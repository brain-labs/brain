/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
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
  BO_IS_VERBOSE = 4,
  BO_IS_OPTIMIZING_O0 = 8,
  BO_IS_OPTIMIZING_O1 = 16
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
     * @brief Returns the optimization level to compile Brain files.
     */
    BrainOption get_optimization();
};

#endif  // ARGS_OPTIONS_H
