return {
    "Shatur/neovim-ayu",
    lazy = false,  -- We want the theme to load immediately on startup
    priority = 1000, -- Load this before all other plugins
    config = function()
        require('ayu').setup({
            mirage = false, -- Set to true for the slightly "greyer" dark version
            overrides = {}, -- You can customize specific colors here later
        })
        require('ayu').colorscheme()
    end,
}
