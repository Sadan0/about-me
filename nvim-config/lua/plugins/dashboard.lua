return {
    {
        'goolord/alpha-nvim',
        dependencies = { 'nvim-tree/nvim-web-devicons' },
        config = function()
            local alpha = require('alpha')
            local dashboard = require('alpha.themes.dashboard')

            -- 1. HEADER (ASCII Art)
            dashboard.section.header.val = {
                [[                                                              ]],
                [[  ██╗   ██╗ ██████╗ ██╗    ██╗   ██╗██████╗ ██╗   ██╗ ██████╗██╗  ██╗ ]],
                [[  ██║   ██║██╔════╝ ██║    ╚██╗ ██╔╝██╔══██╗██║   ██║██╔════╝██║ ██╔╝ ]],
                [[  ██║   ██║██║  ███╗██║     ╚████╔╝ ██████╔╝██║   ██║██║     █████╔╝  ]],
                [[  ██║   ██║██║   ██║██║      ╚██╔╝  ██╔══██╗██║   ██║██║     ██╔═██╗  ]],
                [[  ╚██████╔╝╚██████╔╝███████╗  ██║   ██████╔╝╚██████╔╝╚██████╗██║  ██╗ ]],
                [[   ╚═════╝  ╚═════╝ ╚══════╝  ╚═╝   ╚═════╝  ╚═════╝ ╚═════╝╚═╝   ╚═╝ ]],
                [[                                                              ]],
                [[                          -- Nova Config --                    ]],
            }

            dashboard.section.buttons.val = {
                -- 1. Explicitly sets the directory for Telescope
                dashboard.button("p", "  Prog Jump",
                    ":lua require('telescope.builtin').find_files({ cwd = '~/prog' })<CR>"),

                -- 2. Explicitly sets the C++ directory
                dashboard.button("c", "  C++ Projects",
                    ":lua require('telescope.builtin').find_files({ cwd = '~/prog/cpp' })<CR>"),

                dashboard.button("f", "󰍉  Recent files", ":Telescope oldfiles<CR>"),

                -- 3. Harpoon
                dashboard.button("h", "󱡁  Harpoon",
                    ":lua require('harpoon').ui:toggle_quick_menu(require('harpoon'):list())<CR>"),

                -- 4. Explicitly sets the Config directory
                dashboard.button("s", "  Config",
                    ":lua require('telescope.builtin').find_files({ cwd = '~/.config/nvim' })<CR>"),

                dashboard.button("q", "󰅚  Quit", ":qa<CR>"),
            }


            alpha.setup(dashboard.opts)

            -- Disable folding and indentscope on dashboard
            vim.api.nvim_create_autocmd("FileType", {
                pattern = "alpha",
                callback = function()
                    vim.b.miniindentscope_disable = true
                    vim.opt_local.laststatus = 0 -- Hide statusline on home
                end,
            })
        end
    }
}
