# Recursive-Decent-Parser
A Simple C++ Recursive Decent Parser. This is an example solution of the group competition 1 problem A examination question of NCU compiler course.

## Grammar
### Non-terminals
```
EXPR -> SIG VAL TERM $
TERM -> op SIG VAL TERM
      | λ
VAL -> num
      | lparenthesis EXPR rparenthesis
SIG -> sign
      | λ
```
### Terminals
```
lparenthesis  (
rparenthesis  )
op            [-+*\/]
num           (0|[1-9]\d*)(\.\d+)?
sign          [+-]
```
