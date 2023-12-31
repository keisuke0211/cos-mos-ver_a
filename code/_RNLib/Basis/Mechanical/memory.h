//========================================
// 
// メモリ関連処理
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "../../RNmain.h"

//****************************************
// クラス定義
//****************************************
class CMemory {
public:
	//========== [[[ 関数宣言 ]]]
	std::mutex& GetMutex(void) { return m_memoryMutex; }

	//========================================
	// メモリ確保処理
	//========================================
	template <class T>void Alloc(T** alloc, const int& num = 1, const bool& isMutex = false) {
		
		// 解放しておく
		Release(alloc);

		// 数が0以下の時、終了
		if (num <= 0)
			return;

		// 競合回避の為Mutexをロック
		if (isMutex)
			std::lock_guard<std::mutex> lock(m_memoryMutex);

		// メモリ確保する
		*alloc = new T[num];
	}
	//========================================
	// メモリ確保処理(サイズ指定)
	//========================================
	void Alloc(void** alloc, const size_t& size, const bool& isMutex = true) {
		
		// 解放しておく
		Release(alloc);

		// 競合回避の為Mutexをロック
		if (isMutex)
			std::lock_guard<std::mutex> lock(m_memoryMutex);

		// メモリ確保する
		*alloc = malloc(size);
	}
	//========================================
	// メモリ再確保処理
	//========================================
	template <class T>void ReAlloc(T** alloc, const int& beforeNum, const int& afterNum, const bool& isMutex = false) {

		// 新しい数が0以下の時、解放して終了
		if (afterNum <= 0) {
			Release(alloc);
			return;
		}

		// コピー数が新しい数を越えないよう制御
		int copyNum = beforeNum;
		if (copyNum > afterNum)
			copyNum = afterNum;

		// 新しくメモリを確保する
		T* newAlloc = NULL;
		Alloc<T>(&newAlloc, afterNum, isMutex);

		// 過去の数が0を越えている時、メモリをコピーする
		if (beforeNum > 0) {
			if (*alloc != NULL)
				memcpy(newAlloc, *alloc, sizeof(T) * copyNum);
		}

		// 古い領域を解放し、新しいポインタに入れ替える
		Release(alloc);
		*alloc = newAlloc;
	}
	//========================================
	// メモリ解放処理
	//========================================
	template <class T>void Release(T** release) {

		// NULLなら解放しない
		if (*release == NULL)
			return;

		// 解放
		delete[] (*release);
		*release = NULL;
	}

private:
	//========== [[[ 変数宣言 ]]]
	std::mutex m_memoryMutex;
};