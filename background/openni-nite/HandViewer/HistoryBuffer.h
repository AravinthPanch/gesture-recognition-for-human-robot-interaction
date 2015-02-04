/*******************************************************************************
*                                                                              *
*   PrimeSense NiTE 2.0 - Hand Viewer Sample                                   *
*   Copyright (C) 2012 PrimeSense Ltd.                                         *
*                                                                              *
*******************************************************************************/

#ifndef _HISTORY_BUFFER_H_
#define _HISTORY_BUFFER_H_

template <int BufferSize>
class HistoryBuffer
{
public:
	HistoryBuffer() : m_currentHead(-1), m_size(0)
	{}
	void AddPoint(const nite::Point3f& point)
	{
		++m_currentHead;
		if (m_currentHead == BufferSize)
			m_currentHead = 0;
		m_points[m_currentHead] = point;
		if (m_size < BufferSize)
			++m_size;
	}

	int GetSize() {return m_size;}

	const nite::Point3f& operator[](int index)
	{
		return m_points[(m_currentHead - index + BufferSize) % BufferSize];
	}

private:
	friend class Iterator;

	static const int m_bufferSize = BufferSize;
	nite::Point3f m_points[BufferSize];
	int m_currentHead;
	int m_size;
};


#endif
