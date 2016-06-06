% ftrsm right - lower - size(A) == size(B) - alpha=rand
function errCode = ftrsm_test_14(p)
  errCode = 0;
  try
    addpath(p);
    ff_rand_init();
    F = ff_init_Field();
    n = ff_init_Size();
    alpha = ff_init_Element(F);
    B = ff_init_Matrix(F,n,n);
    A = ff_init_Matrix(F,n,n);
    A = tril(A);
    ff_res = ftrsm(F, 'Right', 'Lower', 'NonUnit', alpha, A, B);
    ref_res = modb( ff_res*A,F);

    eq = isequal(ref_res, modb(alpha*B, F));
    if ~eq
      error('Computation error');
    end
  catch exception;
    disp(exception.message);
    errCode = 1;
  end
end