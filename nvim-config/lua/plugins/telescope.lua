return {
    {
        'nvim-telescope/telescope.nvim',
        dependencies = { 'nvim-lua/plenary.nvim' },
        config = function()
        local builtin = require('telescope.builtin')

        -- Search files in home directory
        vim.keymap.set('n', '<leader>fh', function()
            require('telescope.builtin').find_files({
                cwd = "~",
                hidden = true, -- Optional: includes hidden files like .bashrc
            })
        end, { desc = "Find files in Home" })       -- Keymaps are defined here so 'builtin' is always detected

        vim.keymap.set('n', '<leader>ff', builtin.find_files, { desc = "Find Files", silent = true })
        vim.keymap.set('n', '<leader>fg', builtin.live_grep, { desc = "Live Grep", silent = true })
        end
    },
  {
      'nvim-telescope/telescope-ui-select.nvim',
      config = function()
          require("telescope").setup {
              extensions = {
                ["ui-select"] = {
                  require("telescope.themes").get_dropdown {
                  }
                }
              }
            }
        require("telescope").load_extension("ui-select")
      end
  }
}
