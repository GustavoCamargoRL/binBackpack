// Resolution of the first question of Fundamentals of Algorithms for Optimization
// Example of greedy algorithm
// Author: Gustavo Lima
// Prof: Raphael Kramer

/*Using a greedy algorithm, find a solution to the instance of the knapsack (binary and fractionary) problem presented below:

	Number of items: 14
	Backpack Capacity: 1056
	Item value:
	v = [41 36 51 23 8 65 14 25 34 31 44 47 26 11]
	Item weight:
	p = [419 351 542 238 84 627 132 271 358 322 470 470 258 122]

	- Solve by explaining the step-by-step algorithm and the choices made in each iteration.
*/

#include <vector> 
#include <iostream>	   
#include <algorithm>   


// function to answer the question in binary form
void mochilaBin(int numItens, int capMochila, std::vector<std::pair<int, int>> itens)
{
	std::cout << "\n\nStart of binary method resolution" << std::endl;
	std::vector<std::pair<int, int>> indice; //vector responsible for identifying each item used, the first element being the factor to be ordered
											//and the second element its index, for later identification after sorting.

	//population of the index vector having the item value as the choice of the element to be ordered
	for (int i=0; i < numItens; i++)
	{
		indice.push_back(std::make_pair(itens[i].first,i+1));

	}

	int sobraMochila = capMochila; //variable initialization indicating the available value of the backpack during the iterations
	std::vector<int> selecionados; //declaration of the variable responsible for keeping the indices of the selected items
	int valorTotal = 0;			   //variable initialization indicating the total value stored in the backpack

	std::cout << "Selected greedy criterion: Higher value of items" << std::endl;
	//carrying out the ordering of values ​​in descending order taking the item values ​​as a reference
	//before the ordering of the items.first values ​​= {41,36,51,23,8,65,14,25,34,31,44,47,26,11}
	sort(itens.rbegin(), itens.rend());
	sort(indice.rbegin(), indice.rend());
	std::cout << "Items ordered according to the criteria" << std::endl;
	//after ordering the values ​​items.first = {65,51,47,44,41,36,34,31,26,25,23,14,11,8}

	std::cout << "Start of operation:" << std::endl;
	//start of item selection loop
	for (int i = 0; i < numItens; i++)
	{
		std::cout << "Iteration " << i+1 << ":";
		if (sobraMochila >= itens[i].second) //check if the available space in the backpack is enough to add the current item
		{
			sobraMochila -= itens[i].second;            //decreases the remaining value of the capacity of the backpack by the value of the weight of the current item
			selecionados.push_back(indice[i].second);   //adds the index of the selected item to the selected vector
			valorTotal += itens[i].first;               //updates the total value of the backpack
			std::cout << " The item " << indice[i].second << " fits in the bag and is selected. current total value = " << valorTotal << ", residual capacity = " << sobraMochila << std::endl;
		}
		else if (sobraMochila == 0)  //if the backpack drops the remaining capacity, exit the loop, if not, continue
		{
			std::cout << "Backpack filled... ending execution." << std::endl;
			break;
		}
		else if (sobraMochila <= itens[i].second)
		{
			std::cout << " The item " << indice[i].second << " doesn't fit in the bag" << std::endl;
		}
	}

	//returning the question result to the user
	//selected items = 6 and 1
	//total accumulated value = 106
	// residual capacity of the backpack = 10
	std::cout << "\nFinal result of the binary greedy algorithm" << std::endl;
	std::cout << "Selected items: ";
	for (int i = 0; i<selecionados.size(); i++)
	{
		std::cout << selecionados[i];
		if (i < selecionados.size() - 1)
		{
			std::cout << ", ";
		}
		else 
		{
			std::cout << std::endl;
		}
	}
	std::cout << "Total accumulated value= " << valorTotal << std::endl;
	std::cout << "Backpack residual capacity= " << sobraMochila << std::endl << std::endl;
}

//function to answer the question fractionally
void mochilaFrac(int numItens, double capMochila, std::vector<std::pair<double,double>> itens)
{
	std::cout << "\n\nStart of fractional method resolution" << std::endl;
	std::vector<std::pair<double, int>> indice; //vector responsible for identifying each item using, the first element being the factor to be ordered
												//and the second element its index, for later identification after sorting.
	// fractional operation variables
	double porcent;
	double novoPeso;
	std::cout << "Selected greedy criterion: Lowest quotient of the division between weight/value" << std::endl;
	// population of the index vector having the item value as the choice of the element to be ordered
	//differently from binary, the choice of the element to be ordered will be the quotient of the division between the weight/value
	for (int i = 0; i < numItens; i++)
	{
		indice.push_back(std::make_pair(itens[i].second/itens[i].first, i + 1));
	}

	double sobraMochila = capMochila; //variable initialization indicating the available value of the backpack during the iterations
	std::vector<int> selecionados;   //declaration of the variable responsible for keeping the indices of the selected items
	double valorTotal = 0.0;		//variable initialization indicating the total value stored in the backpack

	//carrying out the ordering of the quotients in ascending order
	//before the ordering of the weight/value ratios = {10,2195 9,75 10,6275 10.3478 10.5 9,64615 9,42857 10.84 10.5294 10.3871 10.6818 10 9,92308 11.0909}
	sort(indice.begin(), indice.end());
	//after ordering the weight/value ratios = {9,42857 9,64615 9,75 9,92308 10 10,2195 10.3478 10.3871 10.5 10.5294 10.6275 10.6818 10.84 11.0909}
	std::cout << "Items ordered according to the criteria" << std::endl;

	std::cout << "Start of operation:" << std::endl;
	//start of item selection loop
	//in this loop the term "index[i].second - 1" will be responsible for operating the values ​​in an orderly way in the disordered vector "items"
	for (int i = 0; i < numItens; i++)
	{
		std::cout << "Iteration " << i+1 << ":";
		if (sobraMochila >= itens[indice[i].second-1].second) //check if the available space in the backpack is enough to add the current item
		{
			sobraMochila -= itens[indice[i].second-1].second; //decreases the remaining value of the capacity of the backpack by the value of the weight of the current item
			selecionados.push_back(indice[i].second);        //adds the index of the selected item to the selected vector
			valorTotal += itens[indice[i].second-1].first;  //updates the total value of the scholarship
			std::cout << " The item " << indice[i].second << " it fits in the bag and is selected. current total value = " << valorTotal << ", capacidade residual = " << sobraMochila << std::endl;
		}
		else if(sobraMochila > 0)  //if the backpack reaches zero remaining capacity, exit the loop, if not, continue
		{
			//calculate how many % we should lower the item's weight to fit in the backpack
			porcent = (itens[indice[i].second-1].second - sobraMochila)/ itens[indice[i].second-1].second;
			novoPeso = itens[indice[i].second-1].second*(1 - porcent); //calculating the new weight of the item to be added
			sobraMochila = sobraMochila - novoPeso;				//update the new remaining weight of the backpack which should always be = 0 now
			selecionados.push_back(indice[i].second);    //adds the index of the last item in the selected vector
			valorTotal += (itens[indice[i].second-1].first)*(1 - porcent);  //calculating the new value of the item according to its fraction
			std::cout << " The item " << indice[i].second << " does not fit in the entire bag. Only" << (1 - porcent) * 100 << "% of item fits in backpack" << std::endl;
			std::cout << "Adding item fraction to bag... Item quantity = " << novoPeso << "w.u. will be added\nCurrent total value = " << valorTotal << ", residual capacity = " << sobraMochila << std::endl;
		}
		else 
		{ 
			std::cout << " Backpack filled... ending execution." << std::endl; 
			break; 
		}  //exit the loop because the backpack has reached its maximum value
	}

	//returning the question result to the user
	//Selected items : 7, 6, 297 units of item weight : 2
	//Total accumulated value = 109.462
	//Residual capacity of the backpack = 0
	std::cout << "\nFinal result of the fractional greedy algorithm" << std::endl;
	std::cout << "selected items: ";
	for (int i = 0; i < selecionados.size(); i++)
	{
		if (i < selecionados.size() - 1)
		{
			std::cout << selecionados[i] << ", ";
		}
		else if (i == selecionados.size() - 1)
		{
			std::cout << novoPeso << " item weight units: " << selecionados[i] << std::endl;
		}
	}
	std::cout << "Total accumulated value= " << valorTotal << std::endl;
	std::cout << "Backpack residual capacity= " << sobraMochila << std::endl;
}

int main(int argc, char *argv[])
{
	int numItens = 14;       //initialization of variable number of items
	int capMochila = 1056;   //iinitialization of the variable capacity of the backpack in weight

	std::vector<int> valItens = {41,36,51,23,8,65,14,25,34,31,44,47,26,11};              //initialization of item value vector
	std::vector<int>  pItens = {419,351,542,238,84,627,132,271,358,322,470,470,258,122};  //initialization of item weight vector
	
	std::vector<std::pair<int,int>> itensB;  //initialization of vector items in pairs of (value,weight) to integer values
	std::vector<std::pair<double, double>> itensF;  //initialization of vector items in pairs of (value,weight) in fractional values

	std::cout << "Beginning of the backpack problem" << std::endl;
	std::cout << "Number of available items =" << numItens << std::endl;
	std::cout << "Backpack capacity = " << capMochila << " w.u." << std::endl;
	std::cout << "Item value= ";
	for(int i = 0; i<numItens; i++)
	{
		std::cout << valItens[i] << ", ";
	}
	std::cout << std::endl << "Item weight= ";
	for (int i = 0; i < numItens; i++)
	{
		std::cout << pItens[i] << ", ";
	}
	std::cout << std::endl;
	//population of the vector itemsB and itemsF with the defined values
	for (int i = 0; i < numItens; i++)
	{
		itensB.push_back(std::make_pair(valItens[i], pItens[i]));
		itensF.push_back(std::make_pair(valItens[i], pItens[i]));

	}

	//call of functions to perform the task
	mochilaBin(numItens, capMochila, itensB);

	mochilaFrac(numItens, capMochila, itensF);

	return 0;
}