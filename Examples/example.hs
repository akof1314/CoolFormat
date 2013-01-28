eval x op y
    | op == "*" = show $ a*b
    | op == "/" = show $ a/b
    | op == "+" = show $ a+b
    | op == "-" = show $ a-b
    where
    a = read x::Double
    b = read y::Double

rpn::[[Char]]->[[Char]]
rpn (x:xs@(y:op:ys))
        |op `elem` ops = rpn (c:ys)
        |otherwise     = rpn (x:(rpn xs))
        where 
        ops = ["*","+","-","/"]
        c   = eval x op y

rpn [x,y] = [x,y] 
rpn [x]      = [x]