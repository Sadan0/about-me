return {
    "stevearc/conform.nvim",
    opts = {
        formatters_by_ft = {
            c = { "clang-format" },
            cpp = { "clang-format" },
            lua = { "stylua" },
            python = { "isort", "black" },
        },
        formatters = {
            ["clang-format"] = {
                prepend_args = {
                    "-style={BasedOnStyle: LLVM, IndentWidth: 4, BreakBeforeBraces: Allman, AllowShortFunctionsOnASingleLine: None}"
                },
            },
        },
        -- Format on save is disabled as requested
        format_on_save = false,
    },
}
