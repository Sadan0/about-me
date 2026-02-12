local ls = require("luasnip")
local s = ls.snippet
local t = ls.text_node
local i = ls.insert_node

return {
  -- Fast print
  s("pr", {
    t("print("), i(1), t(")")
  }),

  -- Main block
  s("main", {
    t({ 'if __name__ == "__main__":', '    ' }),
    i(1, "main()")
  }),
}
