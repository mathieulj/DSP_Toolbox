#ifndef FILTER_H
#define FILTER_H
#include <stdio.h>

<template class TYPE, length>
class FIR_Filter{
	TYPE coefficients[length];
	TYPE memory[length];

	/**
	 * Constructor initialises this FIR filter object to have the given coefficients
	 * @arg aCoefficients Array of coefficients for the FIR filter.
	 */
	FIR_Filter( TYPE aCoefficients[] )
	{
		int i;

		for( i = 0; i < length; i++ )
			coefficients[i] = aCoefficients[i];
	}

	/**
	 * Function filterContinuous() filters the given data using the past data to initialise the filter.
	 * Also saves the last values to the internal memory for the next series of continuous data.
	 *
	 * @arg aData Array of data to filter.
	 * @arg aLength Length of the array of data to pass through the FIR filter (must be larger or equal to the length of this filter).
	 * @arg Returns an array of resulting filter data (of length aLength)
	 */
	TYPE[] filterContinuous( TYPE aData[], int aLength )
	{
		TYPE result[aLength];
		TYPE sum;
		int i, j, offset;

		if( aLength < length )
			throw -1; //Unimplemented as of yet

		//Iterate though points of output
		for( i = 0; i < aLength; i++ )
		{
			sum = 0;

			//Calculate the convolution using the memorised values
			for( j = 0; j < length - i; j++ )
				sum += coefficient[ j ] * memory[ j + i ];

			//Calculate the convolution using the data terms
			for( ; j < length; j++ )
				sum += coefficient[ j ] * aData[ j + i - length ];

			result[i] = sum;
		}

		offset = aLength - length;

		//Memorise the last of the data so that we can keep filtering without interruption
		for( i = offset; i < aLength; i++ )
			memory[ i - offset ] = aData[ i ];

		return result;
	}

	/**
	 * Function filterDiscontinuous() filters the given data using the given coefficients.
	 *
	 * @arg aData Array of data to filter.
	 * @arg aLength Length of the array of data to pass through the FIR filter (must be larger or equal to aFiltLength).
	 * @arg aCoeffs Filter coefficients to use for the filter
	 * @arg aFiltLength Number of coefficients in the filter
	 * @arg Returns an array of resulting filter data (of length aLength - aFiltLength )
	 */
	TYPE[] filterDiscontinuous( TYPE aData[], int aLength, TYPE aCoeffs[], int aFiltLength )
	{
		int i, j;
		int returnLength = aLength - aFiltLength;
		TYPE result[ returnLength ];
		
		if( aLength <= aFiltLength ) 
			return NULL;

		for( i = 0; i < returnLength; i++ )
		{
			result[i] = 0;

			for( j = 0; j < aFiltLength; j++ )
			{
				result[i] += Data[ i + j ]
			}
		}
	}
}

#endif //FILTER_H
