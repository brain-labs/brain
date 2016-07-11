/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#ifndef ARGS_OPTIONS_H
#define ARGS_OPTIONS_H

/**
 * @brief
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
 * @brief Handles all the options passed as arguments to Brain.
 *
 */
class ArgsOptions
{
private:
    ArgsOptions() : _options(BO_NONE) {}
    static ArgsOptions *_instance;
    int _options;
public:
    ArgsOptions(ArgsOptions const&) = delete;
    ArgsOptions& operator=(ArgsOptions const&) = delete;
    /**
     * @brief Returns the AST instance.
     */
    static ArgsOptions* instance();
    /**
     * @brief
     * @param option
     */
    void add_option(BrainOption option);
    /**
     * @brief
     * @param option
     */
    bool has_option(BrainOption option);
    /**
     * @brief
     */
    BrainOption get_optimization();
};

#endif // ARGS_OPTIONS_H
