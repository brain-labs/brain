#include "Bootstrap.h"

// forward declaration of static member.
Bootstrap* Bootstrap::_instance = nullptr;

Bootstrap::Bootstrap()
{
    MODULE_NAME = "brainModule";
    IO_LIB = "/usr/local/include/brain/io.ll";
}

Bootstrap* Bootstrap::instance()
{
    if (_instance == nullptr) {
        _instance = new Bootstrap;
    }

    return _instance;
}

bool Bootstrap::init(int argc, char** argv)
{
    ArgsHandler args_handler(argc, argv);
    Parser parser(args_handler.get_string_file());

    // Create the context and the module
    llvm::LLVMContext llvm_context;

    llvm::SMDiagnostic err;
    std::unique_ptr<llvm::Module> io_module =
        llvm::parseIRFile(llvm::StringRef(IO_LIB), err, llvm_context);

    if (!io_module) {
        err.print(argv[0], llvm::errs());
        return -1;
    }

    llvm::ErrorOr<llvm::Module *> module_or_err = new llvm::Module(MODULE_NAME, llvm_context);
    auto Owner = std::unique_ptr<llvm::Module>(module_or_err.get());
    auto *module = Owner.get();

    // Create the main function: "i32 @main()"
    auto *MainF = llvm::cast<llvm::Function>(module->getOrInsertFunction("main", llvm::Type::getInt32Ty(llvm_context), (llvm::Type *)0));

    // Create the entry block
    auto *basic_block = llvm::BasicBlock::Create(llvm_context,
                                      "EntryBlock", // Conventionnaly called "EntryBlock"
                                      MainF // Add it to "main" function
                                      );

    // Create a builder to add instructions.
    llvm::IRBuilder<> builder(basic_block);
    // Insert the block to function.
    builder.SetInsertPoint(basic_block);

    // Generate IR code from parser.
    parser.code_gen(module, builder);

    // Return 0 to the "main" function.
    builder.CreateRet(builder.getInt32(0));

    if (ArgsOptions::instance()->has_option(BO_IS_EMITTING_AST)) {
        std::cout << "=== Debug Information ===" << "\n";
        parser.debug_description(0);
    }

    if(ArgsOptions::instance()->has_option(BO_IS_EMITTING_LLVM)) {
        std::cout << "=== LLVM IR ===" << "\n";
        std::string dumpStr;
        llvm::raw_string_ostream dumpStrOstream(dumpStr);
        module->print(dumpStrOstream, nullptr);
	io_module->print(dumpStrOstream, nullptr);
        std::cout << dumpStr;
    }

    // Default initialization.
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();
    // Create the execution engine.
    std::string error_str;
    engine_builder = new llvm::EngineBuilder(std::move(Owner));
    execution_engine = engine_builder->setErrorStr(&error_str)
		.setMCJITMemoryManager(std::unique_ptr<llvm::SectionMemoryManager>
							   (new llvm::SectionMemoryManager())).create();

    execution_engine->addModule(std::move(io_module));

    if (!error_str.empty()) {
        std::cout << error_str << "\n";
        exit(0);
    }

    // Finalize the execution engine before use it
    execution_engine->finalizeObject();

    if (ArgsOptions::instance()->has_option(BO_IS_EMITTING_AST) ||
	ArgsOptions::instance()->has_option(BO_IS_EMITTING_LLVM)) {
        // Run the program
        std::cout << "=== Program Output ===" << "\n";
    }

    // No args.
    std::vector<llvm::GenericValue> Args(0);
    llvm::GenericValue gv = execution_engine->runFunction(MainF, Args);

    llvm::llvm_shutdown();

    return 0;
}
