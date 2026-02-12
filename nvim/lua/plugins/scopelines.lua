return {
  {
    "echasnovski/mini.indentscope",
    version = "*",
    config = function()
      -- This code only runs AFTER lazy.nvim downloads the plugin
      require("mini.indentscope").setup({
        symbol = "▎",
        draw = {
          -- This makes it feel snappier
          animation = require("mini.indentscope").gen_animation.none(),
        },
        options = {
          -- Helps keep the line visible when on brackets
          try_as_border = true,
        },
      })
    end,
  },
}
