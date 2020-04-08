# T3: Scheduling com OpenMP
Nome: Crístian Marcos Weber

Disciplina: Programação Paralela

### Código
Link para o código: [OpenMPDemoABC.cpp](OpenMPDemoABC.cpp)

### Saída
Um exemplo da saída do código está apresentada abaixo, com 3 threads em um array de tamanho 30. São apresentados 16 casos diferentes, que variam
de acordo com o uso de tamanho de chunk default ou especificado pelo usuário, e na presença ou ausência de exclusão mútua na insersão de caracteres no array.

```
 ________________
|COM USO DE MUTEX|
 ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
STATIC com especificação de chunk (chunk_size = 5):
BBBBBBBBBBCAAACCCAAACCCAAACCCA
A = 10; B = 10; C = 10;

STATIC sem especificação de chunk:
BBBBBBBBCAAACCCAAAACCCCCAAABBC
A = 10; B = 10; C = 10;

DYNAMIC com especificação de chunk (chunk_size = 5):
ACBBCABBBCAACCBAAABCCCBBAACBAC
A = 10; B = 10; C = 10;

DYNAMIC sem especificação de chunk:
BBBACCAAABCCCCBAAABBBBAAAAABBC
A = 12; B = 11; C = 7;

GUIDED com especificação de chunk (chunk_size = 5):
BBBBAAAABBCCCCCCCCBAAABBBACCCC
A = 8; B = 10; C = 12;

GUIDED sem especificação de chunk:
BBAACCCCCCCCCCCCCCCABBBBAABBBB
A = 5; B = 10; C = 15;

RUNTIME com mutex:
AAAAAAAAAAAAAAAAAAAAAAAAAAAABC
A = 28; B = 1; C = 1;

AUTO com mutex:
AAAAAAAAAACBBCCBBCCBBBBBBCCCCC
A = 10; B = 10; C = 10;

 ________________
|SEM USO DE MUTEX|
 ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
STATIC com especificação de chunk (chunk_size = 5):
CACABABABCCACACCBCC-BBABABAB-B
A = 9; B = 10; C = 9;

STATIC sem especificação de chunk:
BCCBAABACABCACBABCABCABC-BAA-B
A = 10; B = 10; C = 8;

DYNAMIC com especificação de chunk (chunk_size = 5):
BCBABBAACBABCBCACCBBAB-ACAAC-A
A = 10; B = 10; C = 8;

DYNAMIC sem especificação de chunk:
BBCAABACACCAABBBCCACCABCBCAA--
A = 10; B = 8; C = 10;

GUIDED com especificação de chunk (chunk_size = 5):
BAACCBBACACBBACABABCCACBAA-BA-
A = 11; B = 9; C = 8;

GUIDED sem especificação de chunk:
CBBBCBBCBBBBBCBBCBAACA--AAAAAA
A = 9; B = 13; C = 6;

RUNTIME sem mutex:
BBCBCAAACBCABAACCBCAACBABABA--
A = 11; B = 9; C = 8;

AUTO sem mutex:
CACAABABAAACAC-BBCBBBBCBCBC-CC
A = 8; B = 10; C = 10;

```

### Material Consultado
- [Tutorial OpenMP](https://computing.llnl.gov/tutorials/openMP/)
- [OpenMP Scheduling](http://www.inf.ufsc.br/~bosco.sobral/ensino/ine5645/OpenMP_Dynamic_Scheduling.pdf)
