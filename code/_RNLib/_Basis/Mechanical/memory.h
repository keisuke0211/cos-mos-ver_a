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
	template <class T>void Alloc(T** alloc, const int num = 1, const bool isMutex = true) {
		
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
	void Alloc(void** alloc, size_t size, const int num = 1, const bool isMutex = true) {
		
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
	template <class T>void ReAlloc(T** alloc, const int beforeNum, const int afterNum, const bool isMutex = true) {

#if 1
		// 新しい数が0以下の時、解放して終了
		if (afterNum <= 0) {
			Release(alloc);
			return;
		}
		else if (beforeNum == afterNum) {
			// 数の変動が無い時、終了
			return;
		}

		// 新しいサイズ分のメモリを確保
		T* newAlloc = new T[afterNum];

		// コピーする要素数を決定
		int copyNum = (beforeNum < afterNum) ? beforeNum : afterNum;

		// 元のデータを新しい領域にコピー
		memcpy(newAlloc, *alloc, sizeof(T) * copyNum);

		// 新しく追加された要素に対してデフォルトコンストラクタを呼ぶ
		for (int i = beforeNum; i < afterNum; ++i) {
			new (newAlloc + i) T();
		}

		// 古いメモリを解放
		delete[] *alloc;

		// 新しいポインタに入れ替える
		*alloc = newAlloc;
#endif

#if 0
		// 新しい数が0以下の時、解放して終了
		if (afterNum <= 0) {
			Release(alloc);
			return;
		}
		else if (beforeNum <= 0)
		{// 元の数が0以下の時、普通に確保して終了
			Alloc(alloc, afterNum, isMutex);
			return;
		}
		else if (beforeNum == afterNum)
		{// 数の変動が無い時、終了
			return;
		}

		// メモリを最終サイズ分確保(※mallocでコンストラクタを避ける)
		T* newAlloc = (T*)malloc(sizeof(T) * afterNum);

		if (beforeNum < afterNum) {
			//----------------------------------------
			// 数が増えた場合
			//----------------------------------------
			// Newポインタに元のサイズ分のメモリをコピー
			memcpy(newAlloc, *alloc, sizeof(T) * beforeNum);

			// 増えたサイズ分のメモリ確保
			int increasedNum = -beforeNum + afterNum;
			T* increased = new T[increasedNum];

			// Newポインタに増えたサイズ分のメモリをコピー
			memcpy((newAlloc + beforeNum), increased, sizeof(T) * increasedNum);

			// 一時メモリを解放(※freeでデストラクタを避ける)
			free(increased);
		}
		else {
			//----------------------------------------
			// 数が減った場合
			//----------------------------------------
			// Newポインタに必要なサイズ分メモリをコピー
			memcpy(newAlloc, *alloc, sizeof(T) * afterNum);

			// 減った分メモリ確保(※mallocでコンストラクタを避ける)
			int increasedNum = beforeNum - afterNum;
			T* increased = (T*)malloc(sizeof(T) * increasedNum);

			// Decポインタに減った分のメモリをコピー
			memcpy(increased, (*alloc + afterNum), sizeof(T) * increasedNum);

			// 減った分のメモリを解放
			delete[] increased;
		}

		// 古いメモリを解放(※freeでデストラクタを避ける)
		free(*alloc);

		// 新しいポインタに入れ替える
		*alloc = newAlloc;
#endif
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