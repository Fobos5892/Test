// Test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

using namespace std;

//структура для работы с PZU
struct PZU
{
	unsigned int type_adapter; //тип адаптера
	char zero_offset; //смещение нуля
	float calibration_coef; //калибровочный коэффециент
	short serial_number; //заводской номер
	string date_created; //дата изготовления
	int version_software; //версия прошивки
	bool onoff = false; //подключено ли устройство

	PZU()
	{
		type_adapter = 0;
		zero_offset = 0;
		calibration_coef = 0;
		serial_number = 0;
		date_created = "";
		version_software = 0;
		onoff = false;
	}
	~PZU()
	{
		type_adapter = 0;
		zero_offset = 0;
		calibration_coef = 0;
		serial_number = 0;
		date_created = "";
		version_software = 0;
		onoff = false;
	}
};

const int DATA_TO_GPIO2[18] = {
	0,
	15,	//1DO1
	3,	//2DO1
	2,	//3DO1
	0,	//4DO1
	8,	//5DO1
	11,	//6DO1
	7,	//7DO1
	6,	//8DO1
	14,	//9DO1
	12,	//10DO1
	5,	//11DO1
	13,	//12DO1
	28,	//13DO1
	30,	//14DO1
	29,	//15DO1
	4,	//16DO1
	26      //3DO2
};

int PZUDATA[128][8];

int main()
{
    std::cout << "Hello World!\n";

    int x = 4;
    int* p = (int*)x;
    p = 0;
    //cout << p << "\t" << &p << endl;

	char* buf = (char*)malloc(129);
	memset(buf, 0, 129);

	short int* shag;
	shag = (short int*)buf;

	cout << "buf = " << hex << buf << endl;

	for (int i = 0; i < 8; i++)
	{
		cout << hex << shag << "\t" << endl;
		*shag = i;
		cout << hex << *shag << endl;
		++shag;

	}
	cout << endl;
	char* buf2 = (char*)malloc(129);
	//memset(buf2, 0, 129);
	memcpy(buf2, buf, 8 * sizeof(short int));
	shag = (short int*)buf2;
	//for (int i = 0; i < 8; i++)
	//{
		//cout << hex << shag << "\t" << endl;
		//*shag = 0x;
		//cout << hex << *shag << endl;
		//++shag;

	//}

	short int val = 0;
	int index_channel = 0;

	for (int j = 0; j < 8; j++)
	{
		for (int i = 7; i >= 0; --i)
		{
				PZUDATA[j][i] |= 1 << i;
				cout << PZUDATA[j][i] << "\t";
		}
		cout << endl;
	}


	PZU PZU_values;
	for (int j = 0; j < 8; j++)
	{
		val = 0;
		for (int i = 7; i >= 0; --i)
		{
			//val <<= 1;
			//if (PZUDATA[j][i] & (1 << DATA_TO_GPIO2[index_channel + 1]))
			//{
				//val++;
			//}

			cout << hex << (short)*shag << endl;
			if (i < 4) PZU_values.version_software |= (*shag & 0xFF << i * 8);
			else PZU_values.type_adapter |= (*shag & 0xFF << i * 8);
			
		}

		++shag;

		cout << "PZU_values.version = " << PZU_values.version_software << endl;
		cout << "PZU_values.type_adapter = " << PZU_values.type_adapter << endl;

		cout << endl;
		
		cout << hex << val << endl;
		//*g_pPosition = val;
		//++g_pPosition;
	}

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
