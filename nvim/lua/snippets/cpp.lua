local ls = require("luasnip")
local s = ls.snippet
local t = ls.text_node
local i = ls.insert_node

return {
  -- Boilerplate for competitive programming or general C++
  s("main", {
    t({ "#include <iostream>", "", "int main() {", "    " }),
    i(1, "// code here"),
    t({ "", "    return 0;", "}" }),
  }),

  -- Faster For Loop
  s("for", {
    t("for (int i = 0; i < "),
    i(1, "n"),
    t("; ++i) {"),
    t({ "", "    " }),
    i(2),
    t({ "", "}" }),
  }),
}
