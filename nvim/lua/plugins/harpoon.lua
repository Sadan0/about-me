return {
    "ThePrimeagen/harpoon",
    branch = "harpoon2",
    dependencies = { "nvim-lua/plenary.nvim" },
    config = function()
        local harpoon = require("harpoon")

        harpoon:setup({
            settings = {
                save_on_change = true,
                -- This keeps one single list regardless of where you open Neovim
                key = function()
                    return "MY_GLOBAL_LIST"
                end,
            },
        })

        -- ADDING: We force the absolute path (:p) so it's reachable from anywhere
        vim.keymap.set("n", "<leader>a", function()
            local path = vim.fn.expand("%:p")
            harpoon:list():add({
                value = path,
                context = {
                    row = vim.fn.line("."),
                    col = vim.fn.col("."),
                }
            })
            print("Added global: " .. path)
        end)

        -- TOGGLE MENU
        vim.keymap.set("n", "*", function()
            harpoon.ui:toggle_quick_menu(harpoon:list())
        end)

        -- SELECTING / JUMPING
        -- We use a custom select to ensure the buffer loads correctly
        local function jump(index)
            harpoon:list():select(index)
        end

        vim.keymap.set("n", "<leader>1", function() jump(1) end)
        vim.keymap.set("n", "<leader>2", function() jump(2) end)
        vim.keymap.set("n", "<leader>3", function() jump(3) end)
        vim.keymap.set("n", "<leader>4", function() jump(4) end)
    end,
}
