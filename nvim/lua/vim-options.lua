-- Global Settings
vim.g.mapleader = " "
vim.g.maplocalleader = "\\"

-- UI Options
vim.opt.number = true
vim.opt.relativenumber = true
vim.opt.cursorline = true
vim.opt.clipboard = "unnamedplus"
vim.opt.termguicolors = true

-- Tab / Indentation Settings
vim.opt.expandtab = true
vim.opt.tabstop = 4
vim.opt.shiftwidth = 4
vim.opt.softtabstop = 4
vim.opt.autoindent = true
vim.opt.smartindent = true

-- function folding
-- This is the "Magic Fix" for E490:
vim.api.nvim_create_autocmd({ "BufEnter", "BufWinEnter" }, {
    pattern = { "*" },
    callback = function()
        vim.opt.foldmethod = "expr"
        vim.opt.foldexpr = "v:lua.vim.treesitter.foldexpr()"
    end,
})
-- Global Fold Settings
vim.opt.foldmethod = "expr"                          -- Use expressions for folding
vim.opt.foldexpr = "v:lua.vim.treesitter.foldexpr()" -- Use Treesitter for better folding
vim.opt.foldcolumn = "0"                             -- Hide the side fold column (set to "1" to see it)
vim.opt.foldlevel = 99                               -- Open all folds by default when opening a file
vim.opt.foldlevelstart = 99
vim.opt.foldenable = true                            -- Enable folding
