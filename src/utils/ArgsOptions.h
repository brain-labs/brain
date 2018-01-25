/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */


#ifndef ARGS_OPTIONS_H
#define ARGS_OPTIONS_H

/**
 * @brief Enumerates all the options that Brain handles.
 */
typedef enum
{
    BO_NONE = 0,
    BO_IS_EMITTING_LLVM = 1,
    BO_IS_EMITTING_AST = 2,
    BO_IS_EMITTING_CODE = 4,
    BO_IS_VERBOSE = 8,
    BO_IS_OPTIMIZING_O0 = 16,
    BO_IS_OPTIMIZING_O1 = 32,
    BO_IS_GEN_OBJ = 64,
    BO_IS_GEN_ASM = 128,
} BrainOption;

/**
 * @brief Enumerates all the options for the IO library.
 */
typedef enum
{
    IO_REGULAR = 0,
    IO_REPL = 1,
    IO_CUSTOM = 2
} IOOption;


/**
 * @brief This class handles all the options passed as arguments to Brain.   It
 * does so by using an enum of  all options accepted  by  Brain  and an integer
 * which stores by bitwise comparation the values of options used at the moment
 * of execution.
 */
class ArgsOptions
{
private:
    ArgsOptions() : _options(BO_NONE) {}
    /// The singleton object.
    static ArgsOptions *_instance;
    /// Integer value corresponding to the options passed to Brain.
    int _options;
    /// Number of cells available to Brain interpreter.
    int _k_cells_size;
    /// Number of bits of each cell of the tape.
    int _k_cell_bitsize;
    /// Type for the io library
    int _type_io;
public:
    ArgsOptions(ArgsOptions const&) = delete;
    ArgsOptions& operator=(ArgsOptions const&) = delete;
    /**
     * @brief Returns the ArgsOptions instance.
     */
    static ArgsOptions* instance();
    /**
     * @brief Add an option to be used by Brain, it does a bitwise OR on the
     * value to add it to an integer.
     * @param option The option to be added in.
     */
    void add_option(BrainOption option);
    /**
     * @brief Verifies and returns true if an option is present (being used) at
     * the moment of execution, otherwise it returns false.
     * @param option The option to be tested against.
     */
    bool has_option(BrainOption option);
    /**
     * @brief set_cells_size Sets the size of Brain's cells.
     * @param cells_size An integer representing the size of the cells to be
     * set.
     */
    void set_cells_size(int cells_size);
    /**
     * @brief get_cells_size
     * @return An integer corresponding with the size of the Brain cells known
     * as the Brain memory.
     */
    int get_cells_size();
    /**
     * @brief set_cell_bitsize Sets the bitsize of Brain's cells.
     * @param cell_bitsize An integer representing the bitsize of each cell
     * of the Brain tape.
     */
    void set_cell_bitsize(int cell_bitsize);
    /**
     * @brief get_cell_bitsize
     * @return An integer corresponding with the bitsize of each cell of the
     * tape.
     */
    int get_cell_bitsize();
    /**
     * @brief Returns the optimization level to compile Brain files.
     * @returns A BrainOption representing the level of optimization.
     */
    BrainOption get_optimization();
    /**
     * @brief set_io_option Sets the IO style.
     */
    void set_io_option(int type_io);
    /**
     * @brief get_io_option Gets the the IO style.
     */
    int get_io_option();
};

#endif  // ARGS_OPTIONS_H
