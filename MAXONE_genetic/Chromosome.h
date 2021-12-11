#pragma once
#include <vector>
using namespace std;

class Chromosome
{
	vector<int> m_genes;	// ����ü ��Ʈ��
	int m_chromSize;
	int m_fitness;			// ���յ�
	double m_fitnessRate;	// 0 ~ 1 ������ ��. ��ü population���� ���յ� ���� ==> population���� ����
public:
	Chromosome(int size = 5) { resetChromosome(size); };
	~Chromosome() {}

	void resetChromosome(int size); // ���� �ʱ�ȭ�� ���
	void initChromosome();	// ����ü �ʱ�ȭ

	// getters
	int getChromSize() { return m_chromSize; }
	int getFitness() { return m_fitness; }
	double getFitnessRate() { return m_fitnessRate; }
	vector<int> getChromosome() { return m_genes; }

	// setters
	void setFitnessRate(double fr) { m_fitnessRate = fr; }
	void setChromosome(vector<int> genes) { m_genes = genes; }

	void calcFitness();
	void draw();
};

