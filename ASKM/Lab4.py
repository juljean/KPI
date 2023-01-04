import time
from scipy.optimize import minimize, approx_fprime
import pandas as pd

# Given function for Variant 8
function = lambda x: (1.5 - x[0]*(1 - x[1]))**2 + (2.25 - x[0]**(1 - x[1]**2))**2 + (2.625 - x[0]*(1 - x[2]**2))**2
# Given start-vector for Variant 8
x0 = [0, 0, 0, 0]
# Coordinates of minimum value
minimum_coordinates = [3, 0.5, 0, 0]
# Minimum value
minimum_value = 0

# Jacobian for methods of high order
jac = lambda x: approx_fprime(x, function, 0.0001)

start_time = time.time()
# Ukr: Метод Недлера-Міда
NM = minimize(function, x0, args=(), method='Nelder-Mead')
end_time1 = time.time()
# Ukr: Метод спряжених градієнтів
CG = minimize(function, x0, args=(), method='CG')
end_time2 = time.time()
# Urk: Метод Ньютона
NCG = minimize(function, x0, args=(), method='Newton-CG', jac=jac)
end_time3 = time.time()
# Urk: Метод Пауелла
powell = minimize(function, x0, args=(), method='Powell')
end_time4 = time.time()

data = {
    '': ["NM", "CG", "Newton", "Powell"],
    'Minimum of Function': [round(NM.fun, 4), round(CG.fun, 4), round(NCG.fun, 4), round(powell.fun, 4)],
    'Error': [abs(NM.fun-minimum_value), abs(CG.fun-minimum_value), abs(NCG.fun-minimum_value), abs(powell.fun-minimum_value)],
    'Number of iterations': [NM.nit, CG.nit, NCG.nit, powell.nit],
    'Executing time': [end_time1-start_time, end_time2-end_time1, end_time3-end_time2, end_time4-end_time3]
}
df = pd.DataFrame(data)
print(df)
