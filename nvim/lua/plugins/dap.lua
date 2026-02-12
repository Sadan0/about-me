return {
    {
        "mfussenegger/nvim-dap",
        keys = {
            { "<leader>db", desc = "Debug: Toggle [B]reakpoint" },
            { "<leader>dc", desc = "Debug: [C]ontinue" },
            { "<leader>dt", desc = "Debug: [T]oggle UI" },
        },
        dependencies = {
            "rcarriga/nvim-dap-ui",
            "nvim-neotest/nvim-nio",
            "theHamsta/nvim-dap-virtual-text",
            "williamboman/mason.nvim",
        },
        config = function()
            local dap = require("dap")
            local dapui = require("dapui")

            dapui.setup()
            require("nvim-dap-virtual-text").setup({})

            -- 1. ICONS
            vim.fn.sign_define('DapBreakpoint', { text = '🔴', texthl = '', linehl = '', numhl = '' })
            vim.fn.sign_define('DapStopped', { text = '➡️', texthl = '', linehl = '', numhl = '' })

            -- Auto-open/close UI
            dap.listeners.before.attach.dapui_config = function() dapui.open() end
            dap.listeners.before.launch.dapui_config = function() dapui.open() end
            dap.listeners.before.event_terminated.dapui_config = function() dapui.close() end
            dap.listeners.before.event_exited.dapui_config = function() dapui.close() end

            -- 2. ADAPTER
            dap.adapters.codelldb = {
                type = 'server',
                port = "${port}",
                executable = {
                    command = vim.fn.stdpath("data") .. "/mason/bin/codelldb",
                    args = { "--port", "${port}" },
                    detached = false,
                }
            }

            -- 3. CONFIGURATIONS
            dap.configurations.cpp = {
                {
                    name = "Debug Project (Makefile)",
                    type = "codelldb",
                    request = "launch",
                    program = function()
                        local cwd = vim.fn.getcwd()

                        -- A. RELY ON MAKEFILE
                        if vim.fn.filereadable(cwd .. '/Makefile') == 1 then
                            print("Invoking Makefile...")
                            local output = vim.fn.system('make')
                            if vim.v.shell_error ~= 0 then
                                print("Make failed! Error:\n" .. output)
                                return nil
                            end
                        end

                        -- B. DEFINE BINARY PATH
                        local path = cwd .. '/bin/main'

                        -- C. FINAL VERIFICATION
                        if vim.fn.executable(path) == 1 then
                            return path
                        else
                            return vim.fn.input('Executable not found. Path: ', cwd .. '/', 'file')
                        end
                    end,
                    cwd = function() return vim.fn.getcwd() end,
                    stopOnEntry = false,
                    -- ADDED: Support for CLI arguments
                    args = function()
                        local args_str = vim.fn.input('Program arguments: ')
                        return vim.split(args_str, " +")
                    end,
                },
            }
            dap.configurations.c = dap.configurations.cpp

            -- 4. KEYMAPS
            local opts = { noremap = true, silent = true }
            vim.keymap.set('n', '<leader>dt', function() dapui.toggle() end,
                vim.tbl_extend("force", opts, { desc = "Debug: [T]oggle UI" }))
            vim.keymap.set('n', '<leader>dc', function() dap.continue() end,
                vim.tbl_extend("force", opts, { desc = "Debug: [C]ontinue" }))
            vim.keymap.set('n', '<leader>db', function() dap.toggle_breakpoint() end,
                vim.tbl_extend("force", opts, { desc = "Debug: Toggle [B]reakpoint" }))

            -- Navigation Keys
            vim.keymap.set('n', '<leader>dj', function() dap.step_over() end,
                vim.tbl_extend("force", opts, { desc = "Debug: Step Over (Down)" }))
            vim.keymap.set('n', '<leader>dl', function() dap.step_into() end,
                vim.tbl_extend("force", opts, { desc = "Debug: Step Into (Right)" }))
            vim.keymap.set('n', '<leader>dh', function() dap.step_out() end,
                vim.tbl_extend("force", opts, { desc = "Debug: Step Out (Left)" }))

            -- UI Widgets
            vim.keymap.set('n', '<leader>dk', function() require('dap.ui.widgets').hover() end,
                vim.tbl_extend("force", opts, { desc = "Debug: [K]ursor Hover Value" }))
        end
    }
}
