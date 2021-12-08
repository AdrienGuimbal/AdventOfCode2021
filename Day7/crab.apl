input ← ⍎¨','(≠⊆⊢)⊃⊃⎕NGET'/home/adri/Programs/adventOfCode2021/Day7/input.txt' 1

sum_n ← {⍵×(⍵+1)÷2}
fuel ← {+/|(⍵-⍺)}
fuel2 ← {sum_n (⍵ fuel ⍺)}

min_fuel ← {⌊/(⍵ fuel ⊢)¨(⍳⌈/⍵)}
min_fuel2 ← {⌊/(⍵ fuel2 ⊢)¨(⍳⌈/⍵)}
