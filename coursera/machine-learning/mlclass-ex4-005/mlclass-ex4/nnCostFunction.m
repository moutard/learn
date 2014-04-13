function [J grad] = nnCostFunction(nn_params, ...
                                   input_layer_size, ...
                                   hidden_layer_size, ...
                                   num_labels, ...
                                   X, y, lambda)
%NNCOSTFUNCTION Implements the neural network cost function for a two layer
%neural network which performs classification
%   [J grad] = NNCOSTFUNCTON(nn_params, hidden_layer_size, num_labels, ...
%   X, y, lambda) computes the cost and gradient of the neural network. The
%   parameters for the neural network are "unrolled" into the vector
%   nn_params and need to be converted back into the weight matrices.
%
%   The returned parameter grad should be a "unrolled" vector of the
%   partial derivatives of the neural network.
%

% Reshape nn_params back into the parameters Theta1 and Theta2, the weight matrices
% for our 2 layer neural network
Theta1 = reshape(nn_params(1:hidden_layer_size * (input_layer_size + 1)), ...
                 hidden_layer_size, (input_layer_size + 1));

Theta2 = reshape(nn_params((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
                 num_labels, (hidden_layer_size + 1));

% Setup some useful variables
m = size(X, 1);

% You need to return the following variables correctly
J = 0;
Theta1_grad = zeros(size(Theta1));
Theta2_grad = zeros(size(Theta2));

% ====================== YOUR CODE HERE ======================
% Instructions: You should complete the code by working through the
%               following parts.
%
% Part 1: Feedforward the neural network and return the cost in the
%         variable J. After implementing Part 1, you can verify that your
%         cost function computation is correct by verifying the cost
%         computed in ex4.m
%
% refactor labels y (y is a 5000 * 1 size that contains labels.
% transform into a matrix that contains m vectors (10 * 1)
Y = zeros(m, num_labels);
for i=1:m
  Y(i, y(i)) = 1;
end
% a feature x^(i) is a row of X

% add biais unit for each feature.
% a_1 size (n + 1) * m (features * training set)
a_1 = X';
a_biais_1 = [ones(1, m); a_1];

% z_2 size hidden_units * m
z_2 = Theta1 * a_biais_1;

% add biais unit for each feature.
% a_2 size
a_2 = sigmoid(z_2);
a_biais_2 = [ones(1, m); a_2];

z_3 = Theta2 * a_biais_2;

% no need a biais for the output layer.
a_3 = sigmoid(z_3);

h_theta = a_3;
% sum only diagonal elements. Can be improve as we compute a lot of useless element.
% but I guess that's better than a for loop.
J = (1/m) * trace( -Y * log(h_theta) - (1 - Y) * log(1 - h_theta)) ;
% Part 2: Implement the backpropagation algorithm to compute the gradients
%         Theta1_grad and Theta2_grad. You should return the partial derivatives of
%         the cost function with respect to Theta1 and Theta2 in Theta1_grad and
%         Theta2_grad, respectively. After implementing Part 2, you can check
%         that your implementation is correct by running checkNNGradients
%
%         Note: The vector y passed into the function is a vector of labels
%               containing values from 1..K. You need to map this vector into a
%               binary vector of 1's and 0's to be used with the neural network
%               cost function.
%
%         Hint: We recommend implementing backpropagation using a for-loop
%               over the training examples if you are implementing it for the
%               first time.
%
for j=1:m
  delta_3 = a_3(:,j) - Y(j,:)';
  delta_2 = Theta2' * delta_3;
  delta_2 = delta_2 .* a_biais_2(:,j) .* (1 - a_biais_2(:,j));
  Theta1_grad = Theta1_grad + delta_2(2:end) * a_biais_1(:,j)';
  Theta2_grad = Theta2_grad + delta_3 * a_biais_2(:,j)';
end
Theta1_grad = (1/m) * Theta1_grad;
Theta2_grad = (1/m) * Theta2_grad;

% Part 3: Implement regularization with the cost function and gradients.
%
%         Hint: You can implement this around the code for
%               backpropagation. That is, you can compute the gradients for
%               the regularization separately and then add them to Theta1_grad
%               and Theta2_grad from Part 2.
%


% remove the biais before the regularization
Theta1(:,1) = zeros(hidden_layer_size, 1);
Theta2(:,1) = zeros(num_labels, 1);
J = J + (lambda/(2*m)) * (sum(sum(Theta1 .^2)) + sum(sum(Theta2 .^2)));


















% -------------------------------------------------------------

% =========================================================================

% Unroll gradients
grad = [Theta1_grad(:) ; Theta2_grad(:)];


end
