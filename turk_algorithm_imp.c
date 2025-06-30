//find min index

int	find_min_index(stack *a)
{
	int i;
	int	result;

	if (a->top == -1)
		return (-1);
	i = 0;
	result = 0;
	while (i < a->top)
	{
		if (a->data[result] < a->data[i])
			result = i;
		i++;
	}
	return (result);
}


//find max index

int find_max_index(stack *a)
{
	int	i;
	int result;

	if (a->top == -1)
		return (-1);
	i = 0;
	result = 0;
	while (i < a->top)
	{
		if (a->data[result] < a->data[i])
			result = i;
	}
	return (result);
}


//find target for value in B stack
// B boşsa en üste (index 0) yerleştir
// Eğer value'dan küçük sayı yoksa, en büyüğün üstüne yerleştir
// Else Küçük olan sayının üstüne yerleştir

int	find_target_b()




//find target for value in A stack






//rotation cost calculation
// Yukarıdan (ra/rb) kaç adım
// Aşağıdan (rra/rrb) kaç adım  






//push cost calculation
// Basit toplam maliyet (optimizasyon olmadan)





// find cheapest move





//control stack is ordered or not
// En üstten aşağı doğru küçükten büyüğe sıralı olmalı





//rotate top





//optimal push
// B'yi doğru pozisyona getir
// A'yı doğru pozisyona getir
// Push yap





//turk_algorithm
// Eğer zaten sıralıysa çık
// Edge case: 2 eleman varsa
// Edge case: 3 eleman varsa
// İlk iki elemanı B'ye gönder
// B'deki elemanları sırala (büyük üstte)
// A'dan B'ye optimal pushlar (3 eleman kalana kadar)
// A'daki son 3 elemanı sırala
// B'den A'ya geri al
// Son olarak minimum'u en üste getir

