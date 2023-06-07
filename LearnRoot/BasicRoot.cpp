//En C++ os _paquetes_ (como numpy ou matplotlib en python) incluense asi
#include <iostream> //para printear código
#include <vector>//para traballar con vectores
#include <string>//o mesmo para strings

//Para os obxectos propios de ROOT, normalmente comezarán por TXXXX
#include "Rtypes.h"
#include "TFile.h"//para manexar ficheiros
#include "TH1D.h"//T = Clase de ROOT; H1 = histograma 1-dimensional;D = tipo do contido, D = double (decimal de máxima precisión)
#include "TCanvas.h"//para plotear
#include "TF1.h"//funcións 1-dimensionais
#include "TGraph.h"//gráficos de puntos (x,y)
#include "Math/Point3D.h"//para puntos 3D
#include "Math/Vector3D.h"//para vectores
#include "TMath.h"//para funcións matemáticas útiles xa escritas en root

//Incluso podes incluir ficheiros situados en calquera directorio! Tanto .h como .cpp
#include "./Kinematics.cpp"//agora podemos acceder ás funcións defenidas
//aqui como Kinematics::GetEnergy3CM(), por exemplo

//as funcións sempre se escriben así:
//         -------- argumentos (co seu tipo) que toma
int Suma(int a, int b)
//^-- Tipo que devolve    
{
    return a + b;
}

//void non devolve nada
void Suma(int& a)//nunha función a variable normalmente cópiase,
//de forma que calquera modificación que se faga dentro non afecta fora
//porén, se a pasamos como REFERENCIA (&), non se copia, e pódese modificar desde dentro da función!!
{
    a++;//engade 1 a _a_: ++ = a + 1, útil para bucles for
}

//esta función BasicRoot() é unha macro: é a función que se executa cando facemos root BasiRoot.cpp
//non devolve nada (void)
void BasicRoot()
{
    //Moita funcións existen en múltiples paquetes ao mesmo tempo. Para evitar colisións de nomes,
    //especificamos o paquete do que provenhen (namespace) co operador :: , neste caso, estaremos na
    // standard library de c++, std::
    //Printear código
    std::cout<<"Ola mundo!"<<std::endl; //importante usar o operador <<, que redixire a string cara o std::cout: a función cout do namespace std
    //crear un histograma
    //en C++ temos que especificar o tipo do obxecto que creamos sempre
    //afortunadamente, a palabra auto fai que se deduza automaticamente o tipo (+ * se creamos un pointer con new)
    auto* h {new TH1D("h", "Histograma;X [unidades]", 100, -10, 10)};
    //a palabra new crea un obxecto aloxado dinamicamente en memoria
    //é complexo de explicar, pero basicamente o que fai é crear un obxecto (variable) nunha parte
    //da memoria chamada (heap) que non se satura e permite almacenar cousas grandes
    // devolve un POINTER: unha dirección de memoria. normalmente denótase polo tipo + *: TH1D*

    //a outra forma de situar un obxecto en memoria é no stack, que é unha memoria máis rápida
    //pero cun tamaño moi limitado, onde se sitúan tamén os obxectos temporais
    //por exemplo:
    TGraph graph {};
    //este graph será eliminado ao acabarse a función BasicRoot (se o ploteamos, desaparecerá); o histograma h non, só cando saiamos de ROOT (.q)

    //para modificar estes dous tipos de variables
    h->FillRandom("gaus", 1000);// usamos o operador -> para modificar pointers. aquí enchemos 1000 eventos xerados aleatoriamente cunha gaussiana normal
    for(int i = 0; i < 30; i++)
    {
        //para variables _normais_ utilizamos o operator .
        graph.SetPoint(i, i, i * 2);//engadir punto con índice i co valor x e y
    }

    //plotear
    //creamos a superficies para debuxar
    auto* c1 {new TCanvas("c1", "Canvas de proba")};
    c1->cd();//facemos cd no canvas
    //podemos configurar estilos e título
    h->SetTitle("Titulo do histograma;Eixo X;Contas");
    h->SetLineColor(kOrange);//cores aqui: https://root.cern.ch/doc/master/classTColor.html
    h->SetLineWidth(2);
    h->Draw();//case todos os obxetos de root implementan unha función Draw() para automaticamente debuxar :)

    auto* c2 {new TCanvas("c2", "Canvas 2")};
    c2->cd();
    //nomes dos eixos
    graph.SetTitle("Nome do grafico;Eixo X;Eixo Y");
    //estilo
    graph.SetMarkerStyle(24);//https://root.cern.ch/doc/master/classTAttMarker.html
    graph.SetLineWidth(2);
    graph.SetLineColor(kBlue);
    graph.DrawClone("apl");//debuxamos o clon, porque graph elimínase ao acabarse esta función! o clon non!


    //Testeamos as funcións
    int a {1};//initializamos a = 1; tamén o podes escribir
    //int a = 1 (eu prefiro a outra forma pero dá igual)
    auto resultado = Suma(a, 1);//sumamos a  + 1
    std::cout<<"Resultado de Suma(a, 1) =  "<<resultado<<'\n';
    std::cout<<" a despois de Suma() = "<<a<<'\n';
    Suma(a);//chama a Suma(int& a)
    std::cout<<" a despois de Suma() como referencia = "<<a<<'\n';

    //Finalmente, a duración das variables. os {} delimitan a duración da variable, por exemplo
    /*
      {

      int b = 4;
      //b só existe entre estes brackets, e non pode ser accedida fóra
      }
      //b non existe aquí. isto é o que lle pasa á variable graph que definimos anteriormente, será eliminada ao acabarse BasicRoot()
      //o pointer h, pola contra, non, xa que nós non o manexamos directamente... ROOT xa o elimina cando pechemos o progama
      */

    
    std::cout<<"Para saír de ROOT escribe .q"<<std::endl;
}
