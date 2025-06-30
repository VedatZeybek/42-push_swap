#include "push_swap.h"
#include <limits.h>

// Turk Algorithm Helper Functions - DÜZELTILMIŞ VERSIYON

// Stack'te minimum değerin indexini bul
int find_min_index(t_stack *stack) {
    if (stack->top == -1) return -1;
    
    int min_val = stack->data[stack->top];  // En üstten başla
    int min_index = stack->top;
    
    for (int i = stack->top - 1; i >= 0; i--) {  // Aşağı doğru git
        if (stack->data[i] < min_val) {
            min_val = stack->data[i];
            min_index = i;
        }
    }
    return min_index;
}

// Stack'te maximum değerin indexini bul
int find_max_index(t_stack *stack) {
    if (stack->top == -1) return -1;
    
    int max_val = stack->data[stack->top];  // En üstten başla
    int max_index = stack->top;
    
    for (int i = stack->top - 1; i >= 0; i--) {  // Aşağı doğru git
        if (stack->data[i] > max_val) {
            max_val = stack->data[i];
            max_index = i;
        }
    }
    return max_index;
}

// Stack B'de value için target pozisyonu bul - DÜZELTILDI
int find_target_in_b(t_stack *b, int value) {
    if (b->top == -1) 
        return 0; // B boşsa en üste (index 0) yerleştir
    
    int target_index = -1;
    int best_smaller = INT_MIN;
    
    // B'de value'dan küçük olan en büyük sayıyı bul
    for (int i = b->top; i >= 0; i--) {
        if (b->data[i] < value && b->data[i] > best_smaller) {
            best_smaller = b->data[i];
            target_index = i;
        }
    }
    
    // Eğer value'dan küçük sayı yoksa, en büyüğün üstüne yerleştir
    if (target_index == -1) {
        target_index = find_max_index(b);
        // Max'ın üstüne yerleştirmek için bir pozisyon yukarı
        if (target_index < b->top) {
            target_index++;
        } else {
            target_index = 0; // Wrap around
        }
    } else {
        // Küçük olan sayının üstüne yerleştir
        if (target_index < b->top) {
            target_index++;
        } else {
            target_index = 0;
        }
    }
    
    return target_index;
}

// Stack A'da value için target pozisyonu bul - DÜZELTILDI
int find_target_in_a(t_stack *a, int value) {
    if (a->top == -1) 
        return 0;
    
    int target_index = -1;
    int best_bigger = INT_MAX;
    
    // A'da value'dan büyük olan en küçük sayıyı bul
    for (int i = a->top; i >= 0; i--) {
        if (a->data[i] > value && a->data[i] < best_bigger) {
            best_bigger = a->data[i];
            target_index = i;
        }
    }
    
    if (target_index != -1) {
        return target_index;
    } else {
        // Value A'daki herkesten büyükse, min'in üstüne yerleştir
        return find_min_index(a);
    }
}

// Rotation cost hesaplama - DÜZELTILDI
int calculate_rotation_cost(t_stack *stack, int target_index) {
    if (stack->top == -1) return 0;
    
    int stack_size = stack->top + 1;
    
    // Yukarıdan (ra/rb) kaç adım
    int cost_up = (stack->top - target_index + 1) % stack_size;
    
    // Aşağıdan (rra/rrb) kaç adım  
    int cost_down = (target_index + 1) % stack_size;
    
    return (cost_up <= cost_down) ? cost_up : cost_down;
}

// Push cost hesaplama - DÜZELTILDI
int calculate_push_cost(t_stack *a, t_stack *b, int a_index) {
    int cost_a = calculate_rotation_cost(a, a_index);
    int target_b = find_target_in_b(b, a->data[a_index]);
    int cost_b = (b->top >= 0) ? calculate_rotation_cost(b, target_b) : 0;
    
    // Basit toplam maliyet (optimizasyon olmadan)
    return cost_a + cost_b;
}

// En ucuz hareketi bul - DÜZELTILDI
int find_cheapest_move(t_stack *a, t_stack *b) {
    if (a->top == -1) return -1;
    
    int min_cost = calculate_push_cost(a, b, a->top);
    int cheapest_index = a->top;
    
    for (int i = a->top - 1; i >= 0; i--) {
        int cost = calculate_push_cost(a, b, i);
        if (cost < min_cost) {
            min_cost = cost;
            cheapest_index = i;
        }
    }
    
    return cheapest_index;
}

// Stack sıralı mı kontrol et - DÜZELTILDI
int is_sorted(t_stack *a) {
    if (a->top <= 0) return 1; // 0 veya 1 eleman varsa sıralı
    
    // En üstten aşağı doğru küçükten büyüğe sıralı olmalı
    for (int i = a->top; i > 0; i--) {
        if (a->data[i] > a->data[i-1])
			return 0;
    }
    return 1;
}

// Rotation işlemi - DÜZELTILDI
void rotate_to_top(t_stack *stack, int target_index, char stack_name) {
    if (stack->top == -1 || target_index == stack->top) 
        return; // Zaten tepede
    
    int stack_size = stack->top + 1;
    int cost_up = (stack->top - target_index) % stack_size;
    int cost_down = (target_index + 1) % stack_size;
    
    if (cost_up <= cost_down) {
        // ra/rb kullan
        for (int i = 0; i < cost_up; i++) {
            if (stack_name == 'a')
                ra(stack);
            else
                rb(stack);
        }
    } else {
        // rra/rrb kullan
        for (int i = 0; i < cost_down; i++) {
            if (stack_name == 'a')
                rra(stack);
            else
                rrb(stack);
        }
    }
}

// Optimal push işlemi
void execute_optimal_push(t_stack *a, t_stack *b, int a_index) {
    int target_b = find_target_in_b(b, a->data[a_index]);
    
    // B'yi doğru pozisyona getir
    if (b->top >= 0) {
        rotate_to_top(b, target_b, 'b');
    }
    
    // A'yı doğru pozisyona getir
    rotate_to_top(a, a_index, 'a');
    
    // Push yap
    pb(a, b);
}

// Ana Turk algoritması - DÜZELTILDI
void turk_algorithm(t_stack *a, t_stack *b) {
    // Eğer zaten sıralıysa çık
    if (is_sorted(a))
        return;
    
    // Edge case: 2 eleman varsa
    if (a->top == 1) {
        if (a->data[1] > a->data[0])
            sa(a);
        return;
    }
    
    // Edge case: 3 eleman varsa
    if (a->top == 2) {
        sort_threesize_stack(a);
        return;
    }
    
    // İlk iki elemanı B'ye gönder
    pb(a, b);
    if (a->top >= 0)
        pb(a, b);
    
    // B'deki elemanları sırala (büyük üstte)
    if (b->top >= 1 && b->data[b->top] < b->data[b->top-1])
        sb(b);
    
    // A'dan B'ye optimal pushlar (3 eleman kalana kadar)
    while (a->top > 2) {
        int cheapest_index = find_cheapest_move(a, b);
        execute_optimal_push(a, b, cheapest_index);
    }
    
    // A'daki son 3 elemanı sırala
    sort_threesize_stack(a);
    
    // B'den A'ya geri al
    while (b->top >= 0) {
        int target_a = find_target_in_a(a, b->data[b->top]);
        rotate_to_top(a, target_a, 'a');
        pa(a, b);
    }
    
    // Son olarak minimum'u en üste getir
    int min_index = find_min_index(a);
    rotate_to_top(a, min_index, 'a');
}