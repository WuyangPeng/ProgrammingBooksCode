class BinarySearch

  attr_reader :keys, :values
  def initialize(file, size = 0)
    last = ''
    @keys = Array.new(size)
    @values = Array.new(size)
    lines = 0
    hosts = -1
    File.open(file).each_line do |line|
      s = line.split
      article = s[2].intern
      if s[0] != last
        hosts += 1
        @keys[hosts] = s[0]
        @values[hosts] = []
        last = s[0]
      end
      @values[hosts] << [ s[1], article ]
      lines += 1
      STDERR.puts "Line: #{lines}" if (lines % 100000) == 0
    end
  end

  def find(target)
    low = -1
    high = @keys.size
    while (high - low) > 1 do
      probe = (high + low) / 2
      if (@keys[probe] > target)
        high = probe
      else
        low = probe
      end
    end
    if low == -1 || @keys[low] != target
      return nil
    else
      return @values[low]
    end
  end

end
