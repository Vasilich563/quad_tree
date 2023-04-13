#pragma once
#ifndef _QUAD_TREE_

#define _QUAD_TREE_

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

enum data_status
{
	no_data = 0
};

//Квадродерево
template <typename T>
class tree
{
private:
	template<typename T>
	class Node //Узел квадродерева
	{
	public:
		T data;			//Данные, находящиеся в узле
		Node<T>* TL;    //Левый верхний угол
		Node<T>* TR;	//Правый верхний угол
		Node<T>* BL;	//Левый нижний угол
		Node<T>* BR;	//Правый нижний угол
		Node(T data = T(), Node<T>* TL = nullptr, Node<T>* TR = nullptr, Node<T>* BL = nullptr, Node<T>* BR = nullptr)
		{
			this->data = data;
			this->TL = TL;
			this->TR = TR;
			this->BL = BL;
			this->BR = BR;
		}
	};

	Node<T>* root;

	void deleteALL(Node<T>* temp);

	Node<T>* beat_on_quattro(std::vector<std::vector<T>> mat);

	vector<vector<T>> converte_to_matrix(Node<T>* temp);

public:

	tree(std::vector<std::vector<T>> mat);

	~tree()
	{
		deleteALL(this->root);
	}

	vector<vector<T>> converte_to_matrix();

};

//Функция конвертации матрицы в квадродерево
template<typename T>
tree<T>::tree(vector<vector<T>> mat)
{
	this->root = beat_on_quattro(mat);
}

//Рекурсивная функция разбиения матрицы на 4, равных размеров (верхние и нижние левые/правые)
template<typename T>
inline tree<T>::Node<T>* tree<T>::beat_on_quattro(std::vector<std::vector<T>> mat)
{
	if (mat.size() == 1)
	{
		return new Node<T>(mat[0][0]); //если была передана матрица 1 на 1, то создаётся узел, в который записываются её данные
	}
	else
	{
		size_t counter = 0;                                   //начало проверки на равнество всех элементов матрицы
		for (size_t i = 0; i < mat.size(); i++)
		{
			for (size_t j = 0; j < mat.size(); j++)
			{
				if (mat[0][0] == mat[i][j]) ++counter;
			}
		}
		if (counter == (mat.size() * mat.size())) { return new Node<T>(mat[0][0]); } //конец проверки 
		// в случае, если матрица состоит из одинаковых элементов, то она сворачивается в узел, в которыйц записывается данный элемент
		//иначе матрица начинается создание узла без данных (матрица разбивается на 4)
		else
		{
			std::vector<T> temp;
			std::vector<std::vector<T>> top_left, top_right, bottom_left, bottom_right;
			for (size_t i = 0; i < (mat.size() / 2.); i++)
			{
				for (size_t j = 0; j < (mat[0].size() / 2.); j++)
				{
					temp.push_back(mat[i][j]);
				}
				top_left.push_back(temp);
				temp.clear();
			}
			for (size_t i = 0; i < (mat.size() / 2.); i++)
			{
				for (size_t j = (mat[0].size() / 2.); j < mat[0].size(); j++)
				{
					temp.push_back(mat[i][j]);
				}
				top_right.push_back(temp);
				temp.clear();
			}
			for (size_t i = (mat.size() / 2.); i < mat.size(); i++)
			{
				for (size_t j = 0; j < (mat[0].size() / 2.); j++)
				{
					temp.push_back(mat[i][j]);
				}
				bottom_left.push_back(temp);
				temp.clear();
			}
			for (size_t i = (mat.size() / 2.); i < mat.size(); i++)
			{
				for (size_t j = (mat[0].size() / 2.); j < mat[0].size(); j++)
				{
					temp.push_back(mat[i][j]);
				}
				bottom_right.push_back(temp);
				temp.clear();
			}
			//узел указывает на 4 узла, которые создаются на основе 4 матриц, составлявших изначально переданную в функцию
			return new Node<T>(no_data, beat_on_quattro(top_left), beat_on_quattro(top_right), beat_on_quattro(bottom_left), beat_on_quattro(bottom_right));
		}
	}
}

//Рекурсивная функция восстановления повторяющихся элементов матрицы (матрица расширяется до размеров size_of_matrix/2)
template<typename T>
vector<vector<T>> get_normal(vector<vector<T>> old_mat, int size_of_matrix)
{
	if (old_mat.size() == size_of_matrix / 2.) { return old_mat; }
	else
	{
		vector<vector<T>> new_mat;
		new_mat.resize(size_of_matrix / 2.);
		for (int i = 0; i < size_of_matrix / 2.; i++)
		{
			new_mat[i].resize(size_of_matrix / 2.);
		}
		if (old_mat.size() == 1)
		{
			for (int i = 0; i < size_of_matrix / 2.; i++)
			{
				for (int j = 0; j < size_of_matrix / 2.; j++)
				{
					new_mat[i][j] = old_mat[0][0];
				}
			}
			return new_mat;
		}
		else
		{
			if (old_mat.size() == size_of_matrix / 4.)
			{
				for (int i = 0; i < size_of_matrix / 4.; i++)
				{
					for (int j = 0; j < size_of_matrix / 4.; j++)
					{
						new_mat[i][j] = old_mat[0][0];
					}
				}
				for (int i = 0; i < size_of_matrix / 4.; i++)
				{
					for (int j = size_of_matrix / 4.; j < size_of_matrix / 2.; j++)
					{
						new_mat[i][j] = old_mat[0][old_mat.size() - 1];
					}
				}
				for (int i = size_of_matrix / 4.; i < size_of_matrix / 2.; i++)
				{
					for (int j = 0; j < size_of_matrix / 4.; j++)
					{
						new_mat[i][j] = old_mat[old_mat.size() - 1][0];
					}
				}
				for (int i = size_of_matrix / 4.; i < size_of_matrix / 2.; i++)
				{
					for (int j = size_of_matrix / 4.; j < size_of_matrix / 2.; j++)
					{
						new_mat[i][j] = old_mat[old_mat.size() - 1][old_mat.size() - 1];
					}
				}
				return new_mat;
			}
			else { return get_normal(old_mat, (size_of_matrix / 2.)); }
		}
	}
}

//Функция конвертации квадродерева в матрицу
template<typename T>
inline vector<vector<T>> tree<T>::converte_to_matrix()
{
	return this->converte_to_matrix(this->root);
}

//Служеная функция конвертации в матрицу, начиная с заданного узла
template<typename T>
vector<vector<T>> tree<T>::converte_to_matrix(Node<T>* temp)
{
	vector<vector<T>> matrix;
	if (temp->TL == nullptr)
	{
		matrix.resize(1);
		matrix[0].push_back(temp->data);
		return matrix;
	}
	else
	{
		vector<vector<T>> MTL, MTR, BTL, BTR;
		MTL = converte_to_matrix(temp->TL);
		MTR = converte_to_matrix(temp->TR);
		BTL = converte_to_matrix(temp->BL);
		BTR = converte_to_matrix(temp->BR);
		vector<int> temp_to_check_length;
		temp_to_check_length.push_back(MTL.size()); temp_to_check_length.push_back(MTR.size());
		temp_to_check_length.push_back(BTL.size()); temp_to_check_length.push_back(BTR.size());
		int max_size = MTL.size();
		for (int i = 1; i < 4; i++)
		{
			if (max_size < temp_to_check_length[i]) { max_size = temp_to_check_length[i]; }
		}
		temp_to_check_length.clear();
		int size_of_matrix = max_size * 2;
		matrix.resize(size_of_matrix);
		for (int i = 0; i < size_of_matrix; i++)
		{
			matrix[i].resize(size_of_matrix);
		}
		MTL = get_normal(MTL, size_of_matrix);
		MTR = get_normal(MTR, size_of_matrix);
		BTL = get_normal(BTL, size_of_matrix);
		BTR = get_normal(BTR, size_of_matrix);
		for (int i = 0; i < size_of_matrix / 2.; i++)
		{
			for (int j = 0; j < size_of_matrix / 2.; j++)
			{
				matrix[i][j] = MTL[i][j];
			}
		}
		int q = 0;
		for (int i = 0; i < size_of_matrix / 2.; i++, q++)
		{
			int p = 0;
			for (int j = size_of_matrix / 2.; j < size_of_matrix; j++, p++)
			{
				matrix[i][j] = MTR[q][p];
			}
		}
		q = 0;
		for (int i = size_of_matrix / 2.; i < size_of_matrix; i++, q++)
		{
			int p = 0;
			for (int j = 0; j < size_of_matrix / 2.; j++, p++)
			{
				matrix[i][j] = BTL[q][p];
			}
		}
		q = 0;
		for (int i = size_of_matrix / 2.; i < size_of_matrix; i++)
		{
			int p = 0;
			for (int j = size_of_matrix / 2.; j < size_of_matrix; j++)
			{
				matrix[i][j] = BTR[q][p];
			}
		}
		return matrix;
	}
}

//Служебная функция удаления, начиная с заданного узла
template<typename T>
inline void tree<T>::deleteALL(Node<T>* temp)
{
	if (temp->TL != nullptr) deleteALL(temp->TL);
	if (temp->TR != nullptr) deleteALL(temp->TR);
	if (temp->BL != nullptr) deleteALL(temp->BL);
	if (temp->BR != nullptr) deleteALL(temp->BR);
	delete temp;
}

#endif // !_QUAD_TREE_