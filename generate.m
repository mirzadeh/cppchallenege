function generate
rng(0);
format long;

s = 50;
A = rand(s, s);
B = rand(s, s);
X = rand(s, 1);

filename = strcat(num2str(s), 'x', num2str(s), '.txt');
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
    dlmwrite(filename, M, 'delimiter', ' ', '-append', 'precision','%.10f');
    fprintf(file, '\n');
    fclose(file);
end

function write_vector(filename, X, name)
    file = fopen(filename, 'a');
    fprintf(file, '[Vector]\n');
    fprintf(file, '%s %d\n', name, length(X));
    dlmwrite(filename, X', 'delimiter', ' ', '-append', 'precision','%.10f');
    fprintf(file, '\n');
    fclose(file);
end