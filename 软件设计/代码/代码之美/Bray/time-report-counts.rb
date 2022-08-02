counts = {}
counts.default = 0

t1 = Process::times
ARGF.each_line do |line|
  if line =~ %r{GET /ongoing/When/\d\d\dx/(\d\d\d\d/\d\d/\d\d/[^ .]+) }
    counts[$1] += 1
  end
end

t2 = Process::times
keys_by_count = counts.keys.sort { |a, b| counts[b] <=> counts[a] }
keys_by_count[0 .. 9].each do |key|
  puts "#{counts[key]}: #{key}"
end

t3 = Process::times
step1 = t2.utime - t1.utime
step2 = t3.utime - t2.utime

printf "Step 1: %g, Step 2: %g\n", step1, step2
