// Datos dados:
//      I[k] un array con las prendas maximas que compra cada vecino 
//      B[i][k] una matriz con el precio que paga un numero i de prendas el vecino k
//      K el numero de vecinos
//      N el numero de prendas disponibles
//
// venta(i,j) Siendo i el vecino a considerar ahora y j la cantidad de prendas pendientes de vender
// Casos Recursivos:
//      venta(i, j) = max(venta(i-1, j-k) + B[i][k]) para todo 0 <= k <= j y 0 <= k <= I[i]
//
// Casos Base:
//      venta(0,j) = 0          -> Dejamos sin vender j prendas
//      venta(i,0) = 0          -> No nos quedan prendas por vender
//