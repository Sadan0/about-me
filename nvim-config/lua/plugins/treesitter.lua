return {
  "nvim-treesitter/nvim-treesitter",
  build = ":TSUpdate",
  config = function()
    -- We call the setup via the main plugin name to be safe
    local status, treesitter = pcall(require, "nvim-treesitter.configs")
    if not status then
      return
    end

    treesitter.setup({
      ensure_installed = { "lua", "vim", "vimdoc", "python", "c", "cpp" },
      highlight = {
        enable = true,
      },
      indent = {
        enable = false, -- Prevent the "jumping code" issue
      },
    })
  end,
}
