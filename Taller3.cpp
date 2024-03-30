#include <stdio.h>
#include <fstream>  //relacionada al manejo de archivos
#include <iostream> //utilizada para la entrada y salida de datos
#include <limits>   //relacionada a los límites de valores
#include <sstream>  //relacionada a string stream
#include <vector>   //relacionada al manejo de vectores dinámicos
#include <string>   //relacionada manejo de string
#include <queue>    //Libreria de colas
#include <stack>    //libreria de pilas
#include <algorithm>//libreria que permite eliminar espacios de strings

using namespace std;

queue<string> C;
stack<string> stackConvertirAPostFijo;
stack<string> stackEvualuacionPostFijo;

//definimos las colas y las pilas como TDA glopbales en nuestro programa.

void convertidorAPostFija(string);
void evaluacionDePostFija(string);
void tripleteParentesis();
void tripleteCorchete();
void tripleteLlave();
void imprimirStackEAPF();
string imprimirColaC();
void numeroAStack(string);
string removedorDeEspacios(string);

int main()
{
    int opcion;         //entero que nos ayudara a seleccionar la opcion del menu.
    string rescate="";  //string que rescatara la notacion de la opcion 1 para su posterior manejo en la oppcion 2.
    string rescate2;
    //el menu resulta gracias al uso del do while que permite su manejo mas facil
    
    do
    {
        cout << endl<<endl<<"   M E N U     I N I C I A L"<<endl<<endl;
        cout << "1.- Expresion matematica a notación postfija:" << endl;
        cout << "2.- Evaluar expresión postfija:" << endl;
        cout << "3.- Salir:" << endl;
        cout << "Ingrese opcion:    ";
        cin >> opcion;
        if(!cin)
        {
            cout << endl;
            cout << endl <<"¡Se reconoció una entrada incorrecta!" << endl;
            cout << "R E G R E S A N D O ..." << endl;
            cin.clear();
            cin.ignore();
        }
        if (opcion == 1) 
        {
            int opcion1;
            cout << endl<<"Opcion 1...\n"<<endl;
            cout << "1.- Expresion ingresada por teclado:" << endl;
            cout << "2.- Expresion de prueba ((4+3)*(8+3)) :" << endl;
            cout << "3.- Devolver al menu anterior:" << endl;
            cout << "Ingrese opcion:    ";
            cin >> opcion1;
            if(!cin)
            {
                cout << endl;
                cout << endl <<"¡Se reconoció una entrada incorrecta!" << endl;
                cout << "R E G R E S A N D O ..." << endl;
                cin.clear();
                cin.ignore();
            }
            if(opcion1==1)
            {
                string expresionMatematicaTeclado;
                cout << "escriba expresion:  ";
                getline(cin >> ws, expresionMatematicaTeclado);
                rescate2=removedorDeEspacios(expresionMatematicaTeclado);
                convertidorAPostFija(rescate2);
                rescate=imprimirColaC(); //se guarda el retorno de la impresion de cola C, esto se urilizara en la opcion 2.2.
            }
            else if(opcion1==2)
            {
                //string a="([(2+3)*(5-2)]+{16/2})";
                string a="( ( 4 + 3 ) * ( 8 + 3 ) )";
                a=removedorDeEspacios(a);
                convertidorAPostFija(a);
                rescate=imprimirColaC();
            }
            else if(opcion1==3)
            {
                
            }
            else if(opcion1>=4)
            {
                cout<<"Respuesta invalida";
            }
        }
        if (opcion == 2) 
        {
            int opcion2;
            cout << endl<<"Opcion 2...\n"<<endl;
            cout << "1.- Expresion ingresada por teclado:" << endl;
            cout << "2.- Expresion utilizada en la opcion 1:" << endl;
            cout << "3.- Expresion de prueba 23+67+*:" << endl;
            cout << "4.- devolver al menu anterior:" << endl;
            cout << "Ingrese opcion:    ";
            cin >> opcion2;
            if(!cin)
            {
                cout << endl;
                cout << endl <<"¡Se reconoció una entrada incorrecta!" << endl;
                cout << "R E G R E S A N D O ..." << endl;
                cin.clear();
                cin.ignore();
            }
            if(opcion2==1)
            {
                string expresionMatematicaTeclado;
                cout <<"escriba expresion:  ";
                getline(cin >> ws, expresionMatematicaTeclado);
                rescate2=removedorDeEspacios(expresionMatematicaTeclado);
                evaluacionDePostFija(rescate2);
                imprimirStackEAPF();
            }
            else if(opcion2==2)
            {
                if(rescate!="")
                {
                    evaluacionDePostFija(rescate); //utiliza datos guardados de la opcion 1 en la funcion
                    imprimirStackEAPF();
                }
                else
                {
                    cout<<"No se ingresaron datos en la opcion 1";
                }
            }
            else if(opcion2==3)
            {
                string a="2 3 + 6 7 + * ";
                evaluacionDePostFija(a);
                imprimirStackEAPF();
            }
            else if(opcion2==4)
            {
                
            }
            else if(opcion2>=5)
            {
                cout<<"Respuesta invalida";
            }
        }
    }
    while(opcion !=3 );
    

    return 0;
}

void convertidorAPostFija(string expresionMatematica)
{
    vector<char> vectorMatematico(expresionMatematica.begin(), expresionMatematica.end());
    
    for(int i=0;i<expresionMatematica.size();i++)
    {
        if(vectorMatematico[i]==49 || vectorMatematico[i]==50 || vectorMatematico[i]==51 || vectorMatematico[i]==52 || vectorMatematico[i]==53 || vectorMatematico[i]==54 || vectorMatematico[i]==55 || vectorMatematico[i]==56 || vectorMatematico[i]==57 || vectorMatematico[i]==48)
        {
            /*
            Se leen los char en lenguaje scii, se comparan en el vector y segun esto lo iremos ingresando tanto al stack como a la cola.
            */
            string numero;
            numero = vectorMatematico[i];
            C.push(numero);
        }
        else
        {
            
            /*
            en caso de el char no sea un numero del 0 al 9 se ingresara al stack, y si ademas es un parentesis (),[],{} se llamaran
            a sus respectivas funcines.
            */
            
            string operador;
            operador = vectorMatematico[i];
            stackConvertirAPostFijo.push(operador);
            if(stackConvertirAPostFijo.top()==")")
            {
                tripleteParentesis();
            }
            else if(stackConvertirAPostFijo.top()=="]")
            {
                tripleteCorchete();
            }
            else if(stackConvertirAPostFijo.top()=="}")
            {
                tripleteLlave();    
            }    
        }
    }
}

void tripleteParentesis()
{
    /*
    funcion utilizada para cuando se ingressa en el stackConvertirAPostFijo un parentesis, adjuntara todo en su interior para transformarlo
    correctamente a notacion polaca
    */
    
    
    string operadorAritmetico;
    while(stackConvertirAPostFijo.top()!="(")
    {
        if(stackConvertirAPostFijo.top()!=")")
        {
            operadorAritmetico = stackConvertirAPostFijo.top();
            C.push(operadorAritmetico);
        }
        stackConvertirAPostFijo.pop();
    }
    stackConvertirAPostFijo.pop();
}

void tripleteCorchete()
{
    /*
    funcion utilizada para cuando se ingressa en el stackConvertirAPostFijo un corchete, adjuntara todo en su interior para transformarlo
    correctamente a notacion polaca
    */
    
    string operadorAritmetico;
    
    while(stackConvertirAPostFijo.top()!="[")
    {
        operadorAritmetico = stackConvertirAPostFijo.top();
        
        if(stackConvertirAPostFijo.top()!="]")
        {
            C.push(operadorAritmetico);  
        }
        stackConvertirAPostFijo.pop();
    }
    if(stackConvertirAPostFijo.top()=="[")
    {
        stackConvertirAPostFijo.pop();  
    }
}

void tripleteLlave()
{
    
    /*
    funcion utilizada para cuando se ingressa en el stackConvertirAPostFijo una llave, adjuntara todo en su interior para transformarlo
    correctamente a notacion polaca
    */
    string operadorAritmetico;
    
    while(stackConvertirAPostFijo.top()!="{")
    {
        operadorAritmetico = stackConvertirAPostFijo.top();
        
        if(stackConvertirAPostFijo.top()!="}")
        {
            C.push(operadorAritmetico);  
        }
        stackConvertirAPostFijo.pop();
    }
    if(stackConvertirAPostFijo.top()=="{")
    {
        stackConvertirAPostFijo.pop();  
    }
}

void evaluacionDePostFija(string expresionMatematica)
{
    /*
    se ingresa el string resultante de la funcion anterior o el string ingresado por pantalla, se transformara a un arreglo de caracteres
    y se iran guardandop y operando segun su valor. si es un numero del 0 al 9 solo se hará un push en el stack, si es un caracter
    distinto de los otros, se trabajara con la funcion numeroAStack(), y cambiara el resultado segun si es una suma, resta, division
    o multiplicacion.
    */
    
    string auxiliar1, auxiliar2, auxiliar3;
    int numero1, numero2, numero3;
    vector<char> vectorMatematico(expresionMatematica.begin(), expresionMatematica.end());
    for(int i=0;i<expresionMatematica.size();i++)
    {
        string numero;
        numero = vectorMatematico[i];
        if(numero!=" ")
        {
            stackEvualuacionPostFijo.push(numero);    
        }
        
        if(vectorMatematico[i]!=49 || vectorMatematico[i]!=50 || vectorMatematico[i]!=51 || vectorMatematico[i]!=52 || vectorMatematico[i]!=53 || vectorMatematico[i]!=54 || vectorMatematico[i]!=55 || vectorMatematico[i]!=56 || vectorMatematico[i]!=57 || vectorMatematico[i]!=48)
        {
            if(vectorMatematico[i]==42)//MULTIPLICACION
            {
                numeroAStack("*");
            }
            else if(vectorMatematico[i]==43)//SUMA
            {
                numeroAStack("+");
            }
            else if(vectorMatematico[i]==45)//RESTA
            {
                numeroAStack("-");
            }
            else if(vectorMatematico[i]==47)//DIVISION
            {
                numeroAStack("/");
            }
        }
    }
}

void imprimirStackEAPF()
{
    /*
    funcio que se utiliza para imnprimir en pantalla el stack evaluacion a postfija.
    */
    
    cout<<endl<<"evaluacion post fija:    "<<endl;
    while(!stackEvualuacionPostFijo.empty())
    {
        cout<<stackEvualuacionPostFijo.top();
        stackEvualuacionPostFijo.pop();
    }    
}

string imprimirColaC()
{
    /*
    se imprime la cola c al mismo tiempo que se retorna el valor del string para rescatarlo en la funcion para evaluarlo a postfija
    */
    
    string colaRescate;
    cout<<endl<<"Cola:    "<<endl;
    while(!C.empty())
    {
        cout<<C.front();
        colaRescate=colaRescate+C.front();
        C.pop();
    }
    return colaRescate;
}

void numeroAStack(string operador)
{
    /*
    funcion que se utiliza para transformar de un string a un numero gracias al uso de stoi de la libreria de string
    en caso de ser un operador, justamente se opera y se devuelve a la pila.
    
    */
    
    string auxiliar1, auxiliar2, auxiliar3;
    int numero1, numero2 ,numero3;
    stackEvualuacionPostFijo.pop();
    
    auxiliar1   = stackEvualuacionPostFijo.top();
    numero1     = stoi (auxiliar1);
    stackEvualuacionPostFijo.pop();
    
    auxiliar2   = stackEvualuacionPostFijo.top();
    numero2     = stoi (auxiliar2);
    stackEvualuacionPostFijo.pop();
    
    if(operador=="+")
    {
    numero3=numero1+numero2;
    }
    else if(operador=="-")
    {
    numero3=numero1-numero2;
    }
    else if(operador=="*")
    {
    numero3=numero1*numero2;
    }
    else if(operador=="/")
    {
    numero3=numero1/numero2;
    }
    auxiliar3=to_string(numero3);
    stackEvualuacionPostFijo.push(auxiliar3); 
}

string removedorDeEspacios(string str)
{
    //funcion que permite remover espacios de un string gracias a
    //la libreria #include <algorithm>.
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}
