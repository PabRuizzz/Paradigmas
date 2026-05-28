module Main where

main :: IO ()
main = do
    putStrLn "=== Aplicación con Stack ==="
    putStrLn "Ingresa tu nombre:"
    nombre <- getLine
    putStrLn ("Hola, " ++ nombre ++ "!")