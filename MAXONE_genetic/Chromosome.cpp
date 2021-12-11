#include "Chromosome.h"

void Chromosome::resetChromosome(int size)
{
	m_chromSize = size;
	m_fitness = 0;
	m_fitnessRate = 0.f;
	m_genes.resize(size);
	initChromosome();
}

void Chromosome::initChromosome()
{
	double rnd;
	for (int i = 0; i < m_chromSize; i++)
	{
		rnd = rand() / (double)RAND_MAX;
		m_genes[i] = rnd >= 0.5 ? 1 : 0;
	}
	calcFitness();
}

void Chromosome::calcFitness()
{
	m_fitness = 0;
	for (int i = 0; i < m_chromSize; i++)
		m_fitness += m_genes[i];
}
#include <iostream>
void Chromosome::draw()
{
	for (int i = 0; i < m_chromSize; i++)
		cout << m_genes[i] << " ";
	cout << " ==> " << m_fitness << " : " << m_fitness << endl;
}
