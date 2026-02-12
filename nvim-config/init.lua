-- vim defaults
require("vim-options")
-- Bootstrap lazy.nvim
local lazypath = vim.fn.stdpath("data") .. "/lazy/lazy.nvim"
if not (vim.uv or vim.loop).fs_stat(lazypath) then
    local lazyrepo = "https://github.com/folke/lazy.nvim.git"
    vim.fn.system({ "git", "clone", "--filter=blob:none", "--branch=stable", lazyrepo, lazypath })
end
vim.opt.rtp:prepend(lazypath)

-- Setup lazy.nvim (tells it to look in lua/plugins/ folder)
require("lazy").setup("plugins")


--[[  for key mapping and config   ]] --

-- for terminal
local terminal = require("terminal")
local optsilent = { silent = true}
vim.keymap.set('n', '<leader>t', terminal.toggle_terminal, optsilent)
vim.keymap.set('t', '<C-k>', [[<C-\><C-n><C-w>k]], optsilent)

--- Move between windows/splits using Ctrl + direction
vim.keymap.set('n', '<C-h>', '<C-w>h', { desc = "Move to left window" })
vim.keymap.set('n', '<C-l>', '<C-w>l', { desc = "Move to right window" })
vim.keymap.set('n', '<C-j>', '<C-w>j', { desc = "Move to bottom window" })
vim.keymap.set('n', '<C-k>', '<C-w>k', { desc = "Move to top window" })
-- Resize windows using Alt + Arrow Keys
vim.keymap.set('n', '<A-Up>', ':resize +2<CR>', optsilent)
vim.keymap.set('n', '<A-Down>', ':resize -2<CR>', optsilent)
vim.keymap.set('n', '<A-Left>', ':vertical resize -2<CR>', optsilent)
vim.keymap.set('n', '<A-Right>', ':vertical resize +2<CR>', optsilent)

-- file buffer binds
vim.keymap.set('n', '<S-l>', ':BufferLineCycleNext<CR>', optsilent)
vim.keymap.set('n', '<S-h>', ':BufferLineCyclePrev<CR>', optsilent)
vim.keymap.set('n', '<leader>bl', ':BufferLineMoveNext<CR>', optsilent)
vim.keymap.set('n', '<leader>bh', ':BufferLineMovePrev<CR>', optsilent)
vim.keymap.set('n', '<leader>x', ':bdelete<CR>', optsilent)

-- lazy package manager buffer
vim.keymap.set('n', '<leader>l', ':Lazy<CR>', optsilent)
