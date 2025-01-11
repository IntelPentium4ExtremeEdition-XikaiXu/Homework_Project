%xikai xu 400440917 

% Define the differential equation and exact solution
f = @(x, y) 9 * x + y;
exact_solution = @(x) 29 * exp(x) - 9 * x - 9;

% Define the step sizes
h_values = [0.4, 0.2, 0.1];

% Define the range of x-values
x_range = [0, 2];

% Define initial conditions
x0 = 0;
y0 = 20;

% Create a figure
figure;
hold on;
grid on;

% Colors for different step sizes
colors = {'r', 'g', 'b'};
legend_entries = {};

% Iterate over the different step sizes
for i = 1:length(h_values)
    h = h_values(i);
    x_values = x0:h:x_range(2);
    y_values = zeros(1, length(x_values));
    y_values(1) = y0;
    
    % Apply Euler's method
    for j = 1:length(x_values)-1
        y_values(j+1) = y_values(j) + h * f(x_values(j), y_values(j));
    end
    
    % Plot the Euler's method approximation
    plot(x_values, y_values, 'Color', colors{i}, 'LineWidth', 2);
    legend_entries{end+1} = ['Euler''s method, h = ', num2str(h)];
end

% Plot the exact solution
x_exact = linspace(x_range(1), x_range(2), 1000);
y_exact = exact_solution(x_exact);
plot(x_exact, y_exact, 'k', 'LineWidth', 2);
legend_entries{end+1} = 'Exact solution';

% Add labels and legend
xlabel('x');
ylabel('y');
title('Euler''s Method Approximations vs. Exact Solution');
legend(legend_entries, 'Location', 'NorthWest');

hold off;


