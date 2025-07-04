//1 typdef stack 2 init stack 3 isempty isfull 4 push_to_stack pop_from_stack 
//5 sa sb ss pa pb pp ra rb rr rra rrb rrr 6 print stack
//7 free stack and parse_arguemnts and main

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "push_swap_2.h"

int	is_empty(t_stack *stack)
{
	return (stack->top == -1);
}

int is_full(t_stack *stack)
{
	if (stack->top == stack->size -1)
		return (1);
	return (0);
}

t_stack	*init_stack(int *data, int size)
{
	t_stack	*stack;
	int		i;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->data = malloc(sizeof(int) * size); 
	if (!stack->data)
	{
		free(stack);
		return (NULL);
	}
	i = 0;
	if (data)
	{
		while (i < size)
		{
			stack->data[i] = data[i];
			i++;
		}
		stack->top = size - 1;
	}
	else
	{
		stack->top = -1;
	}
	stack->size = size;
	return(stack);
}

int	push_to_stack(t_stack *stack, int value)
{
	if (!is_full(stack))
	{
		stack->top++;
		stack->data[stack->top] = value; 
		return (1);
	}
	return (0);
}

int	pop_from_stack(t_stack *stack)
{
	int	value;

	if (!is_empty(stack))
	{
		value =  stack->data[stack->top];
		stack->data[stack->top] = 0;
		stack->top--;
		return (value);
	}
	return (0);
}

void	sa(t_stack *stack_a)
{
	int temp;
	int	top_index;

	top_index = stack_a->top;
	if (stack_a->top >= 1)
	{
		temp = stack_a->data[top_index];
		stack_a->data[top_index] = stack_a->data[top_index - 1];
		stack_a->data[top_index - 1] = temp;
	}
}

void	sb(t_stack *stack_b)
{
	int temp;
	int	top_index;

	top_index = stack_b->top;
	if (stack_b->top >= 1)
	{
		temp = stack_b->data[top_index];
		stack_b->data[top_index] = stack_b->data[top_index - 1];
		stack_b->data[top_index - 1] = temp;
	}
}

void	ss(t_stack *stack_a, t_stack *stack_b)
{
	sa(stack_a);
	sb(stack_b);
}

void	pa(t_stack *stack_a, t_stack *stack_b)
{
	int	value;

	value = pop_from_stack(stack_b);
	push_to_stack(stack_a, value);
}

void	pb(t_stack *stack_a, t_stack *stack_b)
{
	int	value;

	value = pop_from_stack(stack_a);
	push_to_stack(stack_b, value);
}

void	ra(t_stack *stack_a)
{
	int	i;
	int temp;
	int	temp2;
	int	last_value;

	if (stack_a->top >= 2)
	{
		i = 0;
		temp = stack_a->data[i];
		last_value = stack_a->data[stack_a->top];
		while (i < stack_a->size)
		{
			temp2 = stack_a->data[i + 1];
			stack_a->data[i + 1] = 	temp; 
			temp = temp2;
			i++;
		}
		stack_a->data[0] = last_value;
	}
}

void	rb(t_stack *stack_b)
{
	int	i;
	int temp;
	int	temp2;
	int	last_value;

	if (stack_b->top >= 2)
	{
		i = 0;
		temp = stack_b->data[i];
		last_value = stack_b->data[stack_b->top];
		while (i < stack_b->size)
		{
			temp2 = stack_b->data[i + 1];
			stack_b->data[i + 1] = 	temp; 
			temp = temp2;
			i++;
		}
		stack_b->data[0] = last_value;
	}
}

void	rr(t_stack *stack_a, t_stack *stack_b)
{
	ra(stack_a);
	rb(stack_b);
}

void	rra(t_stack *stack_a)
{
	int	i;
	int temp;
	int	temp2;
	int	last_value;

	if (stack_a->top >= 2)
	{
		i = stack_a->top;
		temp = stack_a->data[stack_a->top];
		last_value = stack_a->data[0];
		while (i >= 0)
		{
			temp2 = stack_a->data[i - 1];
			stack_a->data[i - 1] = 	temp; 
			temp = temp2;
			i--;
		}
		stack_a->data[stack_a->top] = last_value;
	}
}

void	rrb(t_stack *stack_b)
{
	int	i;
	int temp;
	int	temp2;
	int	last_value;

	if (stack_b->top >= 2)
	{
		i = stack_b->top;
		temp = stack_b->data[stack_b->top];
		last_value = stack_b->data[0];
		while (i >= 0)
		{
			temp2 = stack_b->data[i - 1];
			stack_b->data[i - 1] = 	temp; 
			temp = temp2;
			i--;
		}
		stack_b->data[stack_b->top] = last_value;
	}
}

void	rrr(t_stack *stack_a, t_stack *stack_b)
{
	rra(stack_a);
	rrb(stack_b);
}


int	*parse_arguments(int **result, int argc, char **argv)
{
	int i;

	i = 0;
	*result = malloc(sizeof(int) * (argc - 1));
	if (!(*result))
		return (NULL);
	while (i < argc - 1)
	{
		(*result)[argc - 2 - i] = atoi(argv[i + 1]);
		i++;
	}
	return (*result);
}

// void	sort_threesize_stack(t_stack *stack_a)
// {
// 	int top;
// 	int mid;
// 	int bot;

// 	top = stack_a->data[2];
// 	mid = stack_a->data[1];
// 	bot = stack_a->data[0];
// 	if (stack_a->size == 2 && top > mid)
// 		sa(stack_a);
// 	if (stack_a->size != 3)
// 		return ;
// 	if (top > mid && mid > bot && top > bot) //3 2 1
// 	{
// 		sa(stack_a);
// 		rra(stack_a);
// 	}
// 	else if (top > mid && mid < bot && top > bot) //3 1 2
// 		ra(stack_a);
// 	else if (top > mid && mid < bot) //2 1 3
// 		sa(stack_a);
// 	else if (top < mid && mid > bot && top > bot) //2 3 1
// 		rra(stack_a);
// 	else if (top < mid && mid > bot) //1 3 2
// 	{
// 		sa(stack_a);
// 		ra(stack_a);
// 	}
// }

void sort_threesize_stack(t_stack *stack_a) {
    // Güvenlik kontrolü
    if (stack_a->top < 1) 
        return;
    
    // 2 eleman varsa
    if (stack_a->top == 1) {
        if (stack_a->data[stack_a->top] > stack_a->data[stack_a->top - 1])
            sa(stack_a);
        return;
    }
    
    // 3 eleman yoksa çık
    if (stack_a->top != 2)
        return;
    
    // Güvenli indeksleme
    int top = stack_a->data[stack_a->top];      // data[2] - en üst
    int mid = stack_a->data[stack_a->top - 1];  // data[1] - orta  
    int bot = stack_a->data[stack_a->top - 2];  // data[0] - en alt
    
    // Sıralama durumları (stack mantığına göre: alt < orta < üst olmalı)
    if (top > mid && mid > bot && top > bot) {
        // 3 2 1 → [1, 2, 3] yapmalı
        sa(stack_a);   // 2 3 1
        rra(stack_a);  // 1 2 3
    }
    else if (top > mid && mid < bot && top > bot) {
        // 3 1 2 → [1, 2, 3] yapmalı  
        ra(stack_a);   // 1 2 3
    }
    else if (top > mid && mid < bot && top < bot) {
        // 2 1 3 → [1, 2, 3] yapmalı
        sa(stack_a);   // 1 2 3
    }
    else if (top < mid && mid > bot && top > bot) {
        // 2 3 1 → [1, 2, 3] yapmalı
        rra(stack_a);  // 1 2 3
    }
    else if (top < mid && mid > bot && top < bot) {
        // 1 3 2 → [1, 2, 3] yapmalı
        sa(stack_a);   // 3 1 2
        ra(stack_a);   // 1 2 3
    }
    // top < mid && mid < bot durumu zaten sıralı (hiçbir şey yapma)
}

void print_stack(t_stack *stack, char name)
{
	printf("stack %c:\n", name);
	for (int i = stack->top; i >= 0; i--)
		printf("%d\n", stack->data[i]);
}

// Turk Algoritması Debug Versiyonu

void print_stacks_with_title(t_stack *a, t_stack *b, const char *title) {
    printf("\n===========%s===========\n", title);
    printf("stack a:\n");
    for (int i = a->top; i >= 0; i--) {
        printf("%d\n", a->data[i]);
    }
    printf("stack b:\n");
    for (int i = b->top; i >= 0; i--) {
        printf("%d\n", b->data[i]);
    }
    printf("===============================\n");
}

// // Debug versiyonu - her adımı göster
// void turk_algorithm_debug(t_stack *a, t_stack *b) {
//     printf("\n🔍 TURK ALGORITHM DEBUG BAŞLIYOR\n");
//     printf("Initial A top: %d, B top: %d\n", a->top, b->top);
    
//     // Eğer zaten sıralıysa çık
//     if (is_sorted(a)) {
//         printf("✅ Stack zaten sıralı!\n");
//         return;
//     }
    
//     printf("❌ Stack sıralı değil, algoritma başlıyor...\n");
    
//     // Edge cases
//     if (a->top == 1) {
//         printf("🔧 2 elemanlı stack tespit edildi\n");
//         if (a->data[1] > a->data[0]) {
//             printf("Executing: sa\n");
//             sa(a);
//         }
//         return;
//     }
    
//     if (a->top == 2) {
//         printf("🔧 3 elemanlı stack tespit edildi\n");
//         sort_threesize_stack(a);
//         return;
//     }
    
//     printf("📊 Stack boyutu: %d\n", a->top + 1);
    
//     // İlk iki elemanı B'ye gönder
//     printf("\n🔄 İlk iki elementi B'ye gönderiliyor...\n");
//     printf("Executing: pb (pushing %d)\n", a->data[a->top]);
//     pb(a, b);
//     print_stacks_with_title(a, b, "After first pb");
    
//     if (a->top >= 0) {
//         printf("Executing: pb (pushing %d)\n", a->data[a->top]);
//         pb(a, b);
//         print_stacks_with_title(a, b, "After second pb");
//     }
    
//     // B'deki elemanları sırala (büyük üstte olmalı)
//     if (b->top >= 1 && b->data[b->top] < b->data[b->top-1]) {
//         printf("🔄 B stack'i sıralanıyor: sb\n");
//         sb(b);
//         print_stacks_with_title(a, b, "After sorting B");
//     }
    
//     // A'dan B'ye optimal pushlar
//     printf("\n🎯 Optimal push işlemleri başlıyor...\n");
//     int push_count = 0;
//     while (a->top > 2) {
//         push_count++;
//         printf("\n--- Push işlemi #%d ---\n", push_count);
//         printf("A'da kalan eleman sayısı: %d\n", a->top + 1);
        
//         int cheapest_index = find_cheapest_move(a, b);
//         printf("En ucuz eleman indexi: %d, değeri: %d\n", 
//                cheapest_index, a->data[cheapest_index]);
        
//         int cost = calculate_push_cost(a, b, cheapest_index);
//         printf("Bu işlemin maliyeti: %d\n", cost);
        
//         execute_optimal_push(a, b, cheapest_index);
//         print_stacks_with_title(a, b, "After optimal push");
        
//         if (push_count > 10) { // Sonsuz döngü koruması
//             printf("⚠️ Çok fazla push işlemi! Algoritma durduruluyor.\n");
//             break;
//         }
//     }
    
//     // A'daki son 3 elemanı sırala
//     printf("\n🔧 A'daki son 3 eleman sıralanıyor...\n");
//     print_stacks_with_title(a, b, "Before sorting last 3");
//     sort_threesize_stack(a);
//     print_stacks_with_title(a, b, "After sorting last 3");
    
//     // B'den A'ya geri al
//     printf("\n⬅️ B'den A'ya geri alınıyor...\n");
//     int pop_count = 0;
//     while (b->top >= 0) {
//         pop_count++;
//         printf("\n--- Pop işlemi #%d ---\n", pop_count);
//         printf("B'nin tepesindeki: %d\n", b->data[b->top]);
        
//         int target_a = find_target_in_a(a, b->data[b->top]);
//         printf("A'da target pozisyon: %d\n", target_a);
        
//         rotate_to_top(a, target_a, 'a');
//         printf("Executing: pa\n");
//         pa(a, b);
//         print_stacks_with_title(a, b, "After pa");
        
//         if (pop_count > 10) { // Sonsuz döngü koruması
//             printf("⚠️ Çok fazla pop işlemi! Algoritma durduruluyor.\n");
//             break;
//         }
//     }
    
//     // Son olarak minimum'u en üste getir
//     printf("\n🔝 Minimum elemanı en üste getiriliyor...\n");
//     int min_index = find_min_index(a);
//     printf("Minimum eleman indexi: %d, değeri: %d\n", 
//            min_index, a->data[min_index]);
    
//     if (min_index != a->top) {
//         rotate_to_top(a, min_index, 'a');
//         print_stacks_with_title(a, b, "After final rotation");
//     }
    
//     // Final kontrol
//     printf("\n✅ ALGORITMA TAMAMLANDI\n");
//     printf("Final sıralama kontrolü: %s\n", is_sorted(a) ? "SıRALI ✅" : "SIRALI DEĞİL ❌");
// }

// Basit test için
// void test_with_input() {
//     t_stack a, b;
    
//     // [5, 2, 1, 6, 3] - 3 en üstte
//     a.top = 4;
//     a.data[0] = 5;
//     a.data[1] = 2;
//     a.data[2] = 1;
//     a.data[3] = 6;
//     a.data[4] = 3;
    
//     b.top = -1;
    
//     printf("TEST GİRDİSİ: [5, 2, 1, 6, 3]\n");
//     print_stacks_with_title(&a, &b, "INITIAL STATE");
    
//     turk_algorithm_debug(&a, &b);
    
//     printf("\nFINAL RESULT:\n");
//     print_stacks_with_title(&a, &b, "FINAL STATE");
// }

int main(int argc, char **argv) {
	int		*data_a;
	int		*data_b;
	t_stack	*stack_a;
	t_stack	*stack_b;
	
	if (argc < 2) {
		printf("Insufficient Argument\n");
		return (1);
	}
	
	data_a = parse_arguments(&data_a, argc, argv);
	data_b = NULL;
	
	stack_a = init_stack(data_a, argc - 1);
	stack_b = init_stack(NULL, argc - 1);
	
	int num = find_position_in_b(stack_a, 7);
	int num2 = find_position_in_a(stack_a, 7);

	printf("positioni: %d\n", num);
	printf("positioni: %d\n", num2);

	print_stacks_with_title(stack_a, stack_b, "BEFORE");

	turk_algorithm(stack_a, stack_b);
	
	print_stacks_with_title(stack_a, stack_b, "AFTER");

}