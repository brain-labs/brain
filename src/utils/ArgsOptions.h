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
} BrainOption;

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
     * @brief set_cells_size Sets
     * @param cells_size
     */
    void set_cells_size(int cells_size);
    /**
     * @brief get_cells_size
     * @return
     */
    int get_cells_size();
    /**
     * @brief Returns the optimization level to compile Brain files.
     * @returns
     */
    BrainOption get_optimization();
};

#endif  // ARGS_OPTIONS_H
