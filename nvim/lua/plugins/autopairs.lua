return {
    "windwp/nvim-autopairs",
    event = "InsertEnter",
    config = function()
        require("nvim-autopairs").setup({
            check_ts = true, -- Use Treesitter to be smarter (don't add pairs inside strings/comments)
        })

        -- This part makes autopairs and nvim-cmp work together
        -- So if you autocomplete a function, it can add the () automatically
        local cmp_autopairs = require("nvim-autopairs.completion.cmp")
        local cmp = require("cmp")
        cmp.event:on("confirm_done", cmp_autopairs.on_confirm_done())
    end,
}
