
let sud1 = [|[|0; 9; 0; 2; 0; 0; 6; 0; 5|]; [|0; 3; 2; 0; 0; 7; 0; 0; 0|];
             [|0; 7; 0; 9; 0; 5; 0; 0; 8|]; [|0; 1; 0; 0; 0; 0; 0; 0; 0|];
             [|0; 0; 7; 0; 0; 0; 0; 9; 4|]; [|6; 0; 0; 0; 0; 0; 0; 0; 0|];
             [|0; 0; 8; 0; 0; 0; 0; 0; 7|]; [|0; 3; 0; 4; 9; 1; 5; 0; 0|];
             [|0; 0; 0; 0; 0; 0; 0; 0; 0|]|];;

let sud3 = [|[|1; 2; 3; 4; 9; 8; 7; 6; 5|]; [|7; 5; 4; 2; 6; 3; 8; 1; 9|];
             [|6; 9; 8; 5; 1; 7; 4; 3; 2|]; [|4; 6; 7; 1; 8; 2; 9; 5; 3|];
             [|8; 3; 9; 6; 5; 4; 1; 2; 7|]; [|0; 0; 0; 7; 0; 0; 0; 0; 8|];
             [|2; 4; 0; 8; 7; 1; 3; 0; 0|]; [|9; 7; 1; 3; 2; 6; 5; 8; 4|];
             [|3; 8; 6; 9; 4; 5; 2; 7; 1|]|];;

let sud2 = [|[|1; 0; 3; 0; 9; 0; 0; 6; 0|]; [|0; 5; 0; 2; 6; 0; 0; 0; 9|];
             [|0; 0; 8; 5; 1; 7; 0; 3; 2|]; [|4; 0; 0; 0; 0; 2; 0; 0; 0|];
             [|0; 3; 9; 0; 0; 0; 1; 2; 0|]; [|0; 0; 0; 7; 0; 0; 0; 0; 8|];
             [|2; 4; 0; 8; 7; 1; 3; 0; 0|]; [|9; 0; 0; 0; 2; 6; 0; 8; 0|];
             [|0; 8; 0; 0; 4; 0; 2; 0; 1|]|];;




let indice (b,r) = (3*(b/3) +r/3, 3*(b mod 3) + r mod 3);;
indice(5,3);;

let evite tab = let liste = ref [] in
  for i = 0 to 8 do 
    for j = 0 to 8 do 
      if tab.(i).(j) <> 0 then
        liste:= (i,j)::!liste
    done;
  done;
  !liste;;  
evite sud1;;
  
  
let nligne v i sudok = let res = ref true in
  for j = 0 to 8 do 
    if sudok.(i).(j) = v then res:= false
  done;
  !res;;
nligne 3 5 sud1;;

let ncol v j sudok = let res = ref true in
  for i = 0 to 8 do 
    if sudok.(i).(j) = v then res:= false
  done;
  !res;; 
ncol 3 5 sud1;;

let testblock b v sudok = let res = ref true in
  for i = 0 to 8 do 
    let (x,y) = indice (b,i) in
    if sudok.(x).(y) = v then res:= false
  done;
  !res;;
testblock 3 6 sud1;;

let rec appartient x liste = match liste with 
  |[] -> false
  |[a] -> a=x
  |a::reste -> if a=x then true else appartient x reste;;
  
let test v b k sudok = let (i,j) = indice (b,k) in if appartient (i,j) (evite sudok) then false 
else
(testblock b v sudok) && (ncol v j sudok) && (nligne v i sudok);;
test 8 0 0 sud1;;

let fin sudok = let res = ref true in 
  for i = 0 to 8 do
    for j = 0 to 8 do 
      let (x,y) = indice (i,j) in 
      if not(test (sudok.(x).(y)) i j sudok) then res:= false 
    done;
  done; 
  !res;;
fin sud1;;
    
let fin2 sudok = let res = ref true in 
  for i = 0 to 8 do 
    for j = 0 to 8 do
      if sudok.(i).(j) = 0 then res:= false
    done;
  done; 
  res;;

let valeur_case  i j sudok = 
  let rec valeur i j sudok k = if k >=10 then failwith"impossible" else begin let (x,y) = indice (i,j) in 
      if test k x y sudok = true then k
      else valeur i j sudok (k+1) end;
  in valeur i j sudok 1;; 
      
let valeur_case1  b r sudok = 
  let rec valeur b r sudok k = if k >=10 then failwith"impossible" else begin  let (i,j) = indice (b,r) in
      if test k i j sudok = true then k
      else valeur b r sudok (k+1) end;
  in valeur b r sudok 1;;
valeur_case1 1 0 sud1;;

      
let valeur_case2  b r sudok = let k = ref 1 in let res = ref 0 in(*let (i,j) = indice (b,r) in*)
	while !k <= 9 do
		if test !k b r sudok = true then res:=!k
		else k:=!k+1
	done;
	!res;;
valeur_case2 1 0 sud1;;
		
  let rec valeur b r sudok k = if k >=10 then failwith"impossible" else begin  let (i,j) = indice (b,r) in
      if test k i j sudok = true then k
      else valeur b r sudok (k+1) end;
  in valeur b r sudok 1;;

let solsudok sudok =  let liste = evite sudok in let tab = ref sudok in (*if fin sudok = false then failwith"impossible" else *)
  for i = 0 to 8 do 
    for j = 0 to 8 do 
      if appartient (i,j) liste = false then 
        (!tab.(i).(j) <- valeur_case1 i j sudok)
      else 
        ()
    done;
  done;
  !tab;; 
solsudok sud1;;
  
    
    
      

    