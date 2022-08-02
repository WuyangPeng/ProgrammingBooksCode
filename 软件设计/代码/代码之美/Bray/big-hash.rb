class BigHash

  def initialize(file)
    @hash = {}
    lines = 0
    File.open(file).each_line do |line|
      s = line.split
      article = s[2].intern
      if @hash[s[0]]
        @hash[s[0]] << [ s[1], article ]
      else
        @hash[s[0]] = [ s[1], article ]
      end
      lines += 1
      STDERR.puts "Line: #{lines}" if (lines % 100000) == 0
    end
  end

  def find(key)
    @hash[key]
  end

end
