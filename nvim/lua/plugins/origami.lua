return {
    "chrisgrieser/nvim-origami",
    event = "VeryLazy",
    opts = {
        -- Disable the extra text Origami adds to the code
        foldtext = { enabled = false },
    },
    init = function()
        -- 1. FOLDING LOGIC
        vim.opt.foldmethod = "indent"
        vim.opt.foldlevel = 99
        vim.opt.foldlevelstart = 99
        vim.opt.foldenable = true

        -- 3. RESET UI (No icons, no custom columns)
        vim.opt.foldcolumn = "0"             -- Hides the gutter where icons live
        vim.opt.statuscolumn = ""            -- Resets to default Neovim look
        vim.opt.fillchars:append({ fold = " " }) -- Removes the "---" dots

        -- 4. KEYMAPS
        -- Manual control only
        vim.keymap.set("n", "<CR>", "za", { noremap = true, silent = true })
        vim.keymap.set("n", "[[", "zk", { noremap = true, silent = true })
        vim.keymap.set("n", "]]", "zj", { noremap = true, silent = true })
    end,
}
