return {
    {
        "williamboman/mason.nvim",
        config = function()
            require("mason").setup({})
        end
    },
    {
        "williamboman/mason-lspconfig.nvim",
        config = function()
            require("mason-lspconfig").setup({
                ensure_installed = { "lua_ls", "clangd", "pylsp", "vtsls" }
            })
        end
    },
    {
        "neovim/nvim-lspconfig",
        dependencies = { "saghen/blink.cmp" },
        config = function()
            -- Ensure Mason binaries are found
            vim.env.PATH = vim.fn.stdpath("data") .. "/mason/bin" .. ":" .. vim.env.PATH

            -- The Bridge: Get capabilities from blink.cmp
            local capabilities = require('blink.cmp').get_lsp_capabilities()

            -- 1. LUA
            vim.lsp.config('lua_ls', {
                capabilities = capabilities,
                settings = { Lua = { diagnostics = { globals = { "vim" } } } }
            })

            -- 2. C / C++
            vim.lsp.config('clangd', {
                capabilities = capabilities,
                cmd = { "clangd", "--background-index", "--offset-encoding=utf-16" },
                root_markers = { ".git", "compile_commands.json", "CMakeLists.txt", "Makefile" },
            })

            -- 3. PYTHON
            vim.lsp.config('pylsp', {
                capabilities = capabilities,
                settings = { pylsp = { plugins = { pycodestyle = { enabled = false } } } }
            })

            -- 4. JAVASCRIPT
            vim.lsp.config('vtsls', {
                capabilities = capabilities,
                root_markers = { "package.json", ".git" },
            })

            -- ACTIVATE ALL
            vim.lsp.enable('lua_ls')
            vim.lsp.enable('clangd')
            vim.lsp.enable('pylsp')
            vim.lsp.enable('vtsls')

            -- DIAGNOSTIC CONFIGURATION
            vim.diagnostic.config({
                virtual_text = { prefix = "●" },
                float = { border = "rounded", focusable = true },
                underline = true,
                severity_sort = true,
                signs = {
                    text = {
                        [vim.diagnostic.severity.ERROR] = "🚫",
                        [vim.diagnostic.severity.WARN]  = "⚠️",
                        [vim.diagnostic.severity.HINT]  = "🧠",
                        [vim.diagnostic.severity.INFO]  = "💡",
                    },
                },
            })

            -- KEYMAPS
            -- Hover Documentation
            vim.keymap.set('n', 'K', vim.lsp.buf.hover, { desc = "LSP Hover" })

            -- Go to Definition
            vim.keymap.set('n', 'gd', vim.lsp.buf.definition, { desc = "Go to Definition" })

            -- Diagnostic Hover (The floating window you asked for)
            vim.keymap.set('n', '<leader>d', function()
                vim.diagnostic.open_float(nil, { focusable = true })
            end, { desc = "Show Line Diagnostics" })

            -- Manual Formatting (Normal & Visual Mode)
            vim.keymap.set({ "n", "v" }, "<leader>F", function()
                require("conform").format({ async = true, lsp_fallback = true })
            end, { desc = "Format Selection or Buffer" })
        end
    }
}
