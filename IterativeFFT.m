size = 8;
t = linspace(0,1,size);
f = size/4;
out = cos(2*pi*f*t);

fftt = fft(out);

revOrder = bitrevorder(1:size);
out = out(revOrder);

n = log2(size);

for s = 1:n
    m = 2^s;
    wm = exp(2*pi/m);
    for k = 1:m:n
        w = 1;
        for j = 1:m/2-1
            f1 = k+j;
            f2 = k+j+m/2;
            t = w*out(f2);
            u = out(f1);
            w = w*wm;
            out(f1) = u + t;
            out(f2) = u - t;
        end
    end
end

fftt = abs(fftt);
out = abs(out);