function generate
rng(0);
format long;
A = rand(5,5);
B = rand(5,5);
X = rand(5,1);

filename = 'test2.txt';
file = fopen(filename, 'w');
write_matrix(filename, A, 'A');
write_matrix(filename, B, 'B');
write_vector(filename, X, 'X');
write_matrix(filename, A+B, 'A+B');
write_matrix(filename, A-B, 'A-B');
write_matrix(filename, A*B, 'A*B');
write_matrix(filename, A', 'A^T');
write_vector(filename, A*X, 'AX');

fclose(file);
end

function write_matrix(filename, M, name)
    file = fopen(filename, 'a');
    fprintf(file, '[Matrix]\n');
    fprintf(file, '%s %d %d\n', name, size(M));
    dlmwrite(filename, M, 'delimiter', ' ', '-append', 'precision','%.8f');
    fprintf(file, '\n');
    fclose(file);
end

function write_vector(filename, X, name)
    file = fopen(filename, 'a');
    fprintf(file, '[Vector]\n');
    fprintf(file, '%s %d\n', name, length(X));
    fprintf(file, '%.8f ', X);
    fprintf(file, '\n\n');
    fclose(file);
end