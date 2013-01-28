_MATH_KEYWORDS = {
"abs", "acos", "asin", "atan", "atan2", "ceil", "cos", "cosh", "deg", "exp",
"floor", "fmod", "frexp", "ldexp", "log", "log10", "max", "min", "modf", "pi",
"pow", "rad", "random", "randomseed", "sin", "sinh", "sqrt", "tan", "tanh",
}
userFunctions={
[[
        function add2(a,b)
            return a+b
        end
    ]],
[[
        function add3(a,b,c)
            return a+b+c
        end
      ]],
[[
        function perm(n)
            val=1
            for i=1,n do
                val =val*i    
            end
            return val
        end
    ]],
}

function _AddMathKeyword(input)
local ret = input
for _, keyword in pairs(_MATH_KEYWORDS) do
ret = ret:gsub(string.format("([^%%a\.])(%s\(.-\))", keyword), "%1math\.%2")
ret = ret:gsub(string.format("^(%s\(.-\))", keyword), "math\.%1")
end
return ret
end
function Compute(input)
local expr = "return " .. _AddMathKeyword(input)
-- add userDefined function's defination
for i,userfunc in pairs(userFunctions) do
expr=string.gsub(expr,"^",userfunc .. "\n")
end
-- just test the expression
-- if true then
--   error (expr)
-- end
local func = loadstring(expr)
if func == nil then
return "-- 未完整表达式 --"
end
local ret = func()
if ret == math.huge then -- div/0
return "-- 计算错误 --"
end
if ret ~= ret then
-- We rely on the property that NaN is the only value not equal to itself.
return "-- 计算错误 --"
end
return ret
end

ime.register_command("js", "Compute", "计算模式", "none", "输入表达式，例如3*log(4+2)")