counts = {}
counts.default = 0

ARGF.each_line do |line|
  if line =~ %r{GET /ongoing/When/\d\d\dx/(\d\d\d\d/\d\d/\d\d/[^ .]+) }
    counts[$1] += 1
  end
end
