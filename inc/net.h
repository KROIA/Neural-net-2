#pragma once

#include <iostream>
#include <stdio.h>
#include <vector>

#include "layer.h"
#include "activation.h"
#include "net_kernel.cuh"
#include "multiSignalVector.h"
#include "debug.h"








enum Hardware
{
	cpu,
	gpu_cuda
};

//typedef std::vector<float> SignalVector;
//typedef std::vector<SignalVector> MultiSignalVector;



class NET_API Net
{

	typedef float ActFp(float);
	public:
	Net();
	~Net();

	void setDimensions(size_t inputs, size_t hiddenX, size_t hiddenY, size_t outputs);
	void setStreamSize(size_t size);
	size_t getInputCount() const;
	size_t getHiddenXCount() const;
	size_t getHiddenYCount() const;
	size_t getOutputCount() const;

	void setActivation(Activation act);
	Activation getActivation() const;

	void setHardware(enum Hardware ware);
	Hardware getHardware() const;

	bool build();
	void randomizeWeights();
	bool randomizeWeights(size_t from, size_t to);
	static float getRandomValue(float min, float max);

	void setInputVector(float* signalList);
	void setInputVector(size_t stream, float* signalList);
	void setInputVector(const SignalVector& signalList);
	void setInputVector(size_t stream, const SignalVector& signalList);
	void setInputVector(const MultiSignalVector& streamVector);

	void setInput(size_t input, float signal);
	void setInput(size_t stream, size_t input, float signal);
	float getInput(size_t input) const;
	float getInput(size_t stream, size_t input) const;
	const SignalVector& getInputVector(size_t stream = 0);
	const MultiSignalVector &getInputStreamVector();
	const SignalVector& getOutputVector(size_t stream = 0);
	const MultiSignalVector &getOutputStreamVector();

	MultiSignalVector getNetinputStreamVector() const;

	void setWeight(size_t layer, size_t neuron, size_t input, float weight);
	void setWeight(const std::vector<float>&list);
	void setWeight(const float* list);
	void setWeight(const float* list,size_t to);
	void setWeight(const float* list,size_t insertOffset, size_t count);
	float getWeight(size_t layer, size_t neuron, size_t input) const;
	const float* getWeight() const;
	size_t getWeightSize() const;


	void calculate();
	void calculate(size_t stream);
	void calculate(size_t streamBegin, size_t streamEnd);

	protected:

	void CPU_calculate(size_t streamBegin, size_t streamEnd); // including begin, excluding end
	void GPU_CUDA_calculate(size_t streamBegin, size_t streamEnd);
	static void CPU_calculateNet(float* weights, float* signals, float* outpuSignals, float* netinputList,
							 size_t inputCount, size_t hiddenX, size_t hiddenY, size_t outputCount, ActFp *activation);
	static void CPU_calculateLayer(float* weights, float* inputSignals, float* outputSignals, float* netinputList,
							   size_t neuronCount, size_t inputSignalCount, ActFp* activation);

	void transferWeightsToDevice();
	void transferWeightsToHost();
	void transferSignalsToDevice();
	void transferSignalsToHost();
	void buildDevice();
	void destroyDevice();
	void buildHostWeights();
	void destroyHostWeights();

	size_t m_inputs;
	size_t m_hiddenX;
	size_t m_hiddenY;
	size_t m_outputs;

	size_t m_streamSize;

	size_t m_neuronCount;
	size_t m_weightsCount;

	Activation m_activation;
	ActFp* m_activationFunc;

	MultiSignalVector m_inputStream;
	MultiSignalVector m_outputStream;
	MultiSignalVector m_netinputList;

	//float** m_inputSignalList;
	float* m_weightsList;
	//float** m_outputSingalList;
	bool   m_built;

	// Extern hardware
	Hardware m_hardware;
	float** d_inputSignalList;
	float** h_d_inputSignalList;
	float** d_netinputList;
	float** h_d_netinputList;
	float* d_weightsList;
	float** d_outputSingalList;
	float** h_d_outputStream;

	private:
	static float activation_linear(float inp);
	static float activation_gauss(float inp);
	static float activation_sigmoid(float inp);

};

