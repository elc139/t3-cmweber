#include <string>
#include <iostream>
#include <omp.h>

using namespace std;

void spendSomeTime();

class SharedArray {
private:
    char* array;
    int index;
    int size;
public:
    SharedArray(int size)
    {
   	 this->size = size;
   	 this->index = 0;
   	 this->array = new char[size];
   	 fill(array, array+size, '-');
    }

    int returnSize()
    {
   	 return this->size;
    }

    char returnChar(int id)
    {
   	 return array[id];
    }

    string returnString()
    {
   	 return string(array, array+size);
    }

    void reset_array()
    {
   	 index = 0;
   	 fill(array, array+size, '-');
    }

    void addCharMutex()
    {
   	 #pragma omp critical
   	 {
    	array[index] = 'A' + omp_get_thread_num();
    	spendSomeTime();
   	 index++;
   	 }
    }

    void addChar()
    {
   	 array[index] = 'A' + omp_get_thread_num();
   	 spendSomeTime();
   	 index++;
    }

    int count_char(char c)
    {
    	int count = 0;
   	 for(int i = 0; i < size; i++){
   		 if(array[i] == c) count++;
   	 }

   	 return count;
    }

};

class ArrayFiller {
private:
    int chunk_size;
    int nthreads;
    SharedArray *shArray;
public:
    ArrayFiller(int nthreads, int size, int chunk_size)
    {
   	 this->shArray = new SharedArray(size);
   	 this->chunk_size = chunk_size;
   	 this->nthreads = nthreads;
    }

    void ScheduledFill()
    {
   	 bool useMutex = true;
   	 cout << " ________________\n|COM USO DE MUTEX|\n ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n";
   	 this->StaticArrayFill(chunk_size,useMutex); this->StaticArrayFill(0,useMutex);
   	 this->DynamicArrayFill(chunk_size,useMutex); this->DynamicArrayFill(0,useMutex);
    	this->GuidedArrayFill(chunk_size,useMutex); this->GuidedArrayFill(0,useMutex);
   	 this->RuntimeArrayFill(useMutex);
   	 this->AutoArrayFill(useMutex);

    	cout << " ________________\n|SEM USO DE MUTEX|\n ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n";
    	this->StaticArrayFill(chunk_size,!useMutex); this->StaticArrayFill(0,!useMutex);
    	this->DynamicArrayFill(chunk_size,!useMutex); this->DynamicArrayFill(0,!useMutex);
    	this->GuidedArrayFill(chunk_size,!useMutex); this->GuidedArrayFill(0,!useMutex);
    	this->RuntimeArrayFill(!useMutex);
    	this->AutoArrayFill(!useMutex);
    }

    void StaticArrayFill(int specified_chunk, bool useMutex)
    {
    	if(!specified_chunk){

        	cout << "STATIC sem especificação de chunk:\n";

        	#pragma omp parallel for schedule(static) num_threads(nthreads)
        	for(int i = 0; i < shArray->returnSize(); i++){
            	if(useMutex) shArray->addCharMutex();
   			 else shArray->addChar();
        	}

    	}else{

        	cout << "STATIC com especificação de chunk (chunk_size = " << chunk_size << "):\n";

        	#pragma omp parallel for schedule(static, chunk_size) num_threads(nthreads)
        	for(int i = 0; i < shArray->returnSize(); i++){
            	if(useMutex) shArray->addCharMutex();
   			 else shArray->addChar();
   		 }
    	}

    	printArrayInfo();
    	shArray->reset_array();
	}

    void DynamicArrayFill(int specified_chunk, bool useMutex)
    {
    	if(!specified_chunk){

        	cout << "DYNAMIC sem especificação de chunk:\n";

        	#pragma omp parallel for schedule(dynamic) num_threads(nthreads)
        	for(int i = 0; i < shArray->returnSize(); i++){
            	if(useMutex) shArray->addCharMutex();
   			 else shArray->addChar();
        	}

    	}else{

        	cout << "DYNAMIC com especificação de chunk (chunk_size = " << chunk_size << "):\n";

        	#pragma omp parallel for schedule(dynamic, chunk_size) num_threads(nthreads)
        	for(int i = 0; i < shArray->returnSize(); i++){
   			 if(useMutex) shArray->addCharMutex();
            	else shArray->addChar();
        	}
    	}

    	printArrayInfo();
    	shArray->reset_array();

	}

    void GuidedArrayFill(int specified_chunk, bool useMutex)
	{
    	if(!specified_chunk){

        	cout << "GUIDED sem especificação de chunk:\n";

        	#pragma omp parallel for schedule(guided) num_threads(nthreads)
        	for(int i = 0; i < shArray->returnSize(); i++){
   			 if(useMutex) shArray->addCharMutex();
            	else shArray->addChar();
        	}

    	}else{

        	cout << "GUIDED com especificação de chunk (chunk_size = " << chunk_size << "):\n";

        	#pragma omp parallel for schedule(guided, chunk_size) num_threads(nthreads)
        	for(int i = 0; i < shArray->returnSize(); i++){
   			 if(useMutex) shArray->addCharMutex();
            	else shArray->addChar();
        	}
    	}

    	printArrayInfo();
    	shArray->reset_array();
	}

    void RuntimeArrayFill(bool useMutex = true)
	{
    	cout << "RUNTIME ";
   	 if(useMutex) cout << "com mutex:" << endl;
   	 else cout << "sem mutex:" << endl;

    	#pragma omp parallel for schedule(runtime) num_threads(nthreads)
    	for(int i = 0; i < shArray->returnSize(); i++){
        	if(useMutex) shArray->addCharMutex();
   		 else shArray->addChar();
    	}

    	printArrayInfo();
    	shArray->reset_array();
	}

	void AutoArrayFill(bool useMutex = true)
	{
    	cout << "AUTO ";
   	 if(useMutex) cout << "com mutex:" <<endl ;
   	 else cout << "sem mutex:" << endl;

    	#pragma omp parallel for schedule(auto) num_threads(nthreads)
    	for(int i = 0; i < shArray->returnSize(); i++){
        	if(useMutex)shArray->addCharMutex();
   		 else shArray->addChar();
    	}

    	printArrayInfo();
    	shArray->reset_array();
	}


    void printArrayInfo()
    {
   	 for(int i = 0; i < shArray->returnSize(); i++){
   		 cout << shArray->returnChar(i);
   	 }
   	 cout << '\n';

   	 for(int j = 0; j < nthreads; j++){
   		 cout <<  char('A' + j) << " = " << shArray->count_char('A' + j) << "; ";
   	 }
   	 cout << "\n\n";
    }
};

void spendSomeTime()
{
    for(int i = 0; i < 1000; i++){
   	 for(int j = 0; j < 1000; j++){
   		 //These loops shouldn't be removed by the compiler
   	 }
    }
}

int main(int argc, char *argv[]){

    if(argc != 4){
   	 cout<< "Uso: " << argv[0] << "<num_threads> <array_size> <chunk_size>" << endl;
   	 return 0;
    }
    else{
   	 if(atoi(argv[1]) <= 0 || atoi(argv[2]) <= 0 || atoi(argv[3]) <= 0){
   		 cout << "Argumentos devem ser numeros > 0" << endl;
   		 return 0;
   	 }
    }

    ArrayFiller f(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    f.ScheduledFill();

    return 0;
}
