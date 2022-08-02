namespace WeatherClient
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.radioButtonCelsius = new System.Windows.Forms.RadioButton();
            this.radioButtonFahrenheit = new System.Windows.Forms.RadioButton();
            this.buttonGetWeather = new System.Windows.Forms.Button();
            this.labelCity = new System.Windows.Forms.Label();
            this.labelWeatherCondition = new System.Windows.Forms.Label();
            this.labelTemperature = new System.Windows.Forms.Label();
            this.textCity = new System.Windows.Forms.TextBox();
            this.textWeatherCondition = new System.Windows.Forms.TextBox();
            this.textTemperature = new System.Windows.Forms.TextBox();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.radioButtonFahrenheit);
            this.groupBox1.Controls.Add(this.radioButtonCelsius);
            this.groupBox1.Location = new System.Drawing.Point(13, 28);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(135, 86);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Temperature Type";
            // 
            // radioButtonCelsius
            // 
            this.radioButtonCelsius.AutoSize = true;
            this.radioButtonCelsius.Location = new System.Drawing.Point(19, 30);
            this.radioButtonCelsius.Name = "radioButtonCelsius";
            this.radioButtonCelsius.Size = new System.Drawing.Size(58, 17);
            this.radioButtonCelsius.TabIndex = 0;
            this.radioButtonCelsius.TabStop = true;
            this.radioButtonCelsius.Text = "Celsius";
            this.radioButtonCelsius.UseVisualStyleBackColor = true;
            // 
            // radioButtonFahrenheit
            // 
            this.radioButtonFahrenheit.AutoSize = true;
            this.radioButtonFahrenheit.Location = new System.Drawing.Point(19, 54);
            this.radioButtonFahrenheit.Name = "radioButtonFahrenheit";
            this.radioButtonFahrenheit.Size = new System.Drawing.Size(75, 17);
            this.radioButtonFahrenheit.TabIndex = 1;
            this.radioButtonFahrenheit.TabStop = true;
            this.radioButtonFahrenheit.Text = "Fahrenheit";
            this.radioButtonFahrenheit.UseVisualStyleBackColor = true;
            // 
            // buttonGetWeather
            // 
            this.buttonGetWeather.Location = new System.Drawing.Point(12, 135);
            this.buttonGetWeather.Name = "buttonGetWeather";
            this.buttonGetWeather.Size = new System.Drawing.Size(135, 23);
            this.buttonGetWeather.TabIndex = 1;
            this.buttonGetWeather.Text = "Get Weather";
            this.buttonGetWeather.UseVisualStyleBackColor = true;
            this.buttonGetWeather.Click += new System.EventHandler(this.OnGetWeather);
            // 
            // labelCity
            // 
            this.labelCity.AutoSize = true;
            this.labelCity.Location = new System.Drawing.Point(185, 38);
            this.labelCity.Name = "labelCity";
            this.labelCity.Size = new System.Drawing.Size(27, 13);
            this.labelCity.TabIndex = 2;
            this.labelCity.Text = "City:";
            // 
            // labelWeatherCondition
            // 
            this.labelWeatherCondition.AutoSize = true;
            this.labelWeatherCondition.Location = new System.Drawing.Point(12, 185);
            this.labelWeatherCondition.Name = "labelWeatherCondition";
            this.labelWeatherCondition.Size = new System.Drawing.Size(98, 13);
            this.labelWeatherCondition.TabIndex = 3;
            this.labelWeatherCondition.Text = "Weather Condition:";
            // 
            // labelTemperature
            // 
            this.labelTemperature.AutoSize = true;
            this.labelTemperature.Location = new System.Drawing.Point(12, 218);
            this.labelTemperature.Name = "labelTemperature";
            this.labelTemperature.Size = new System.Drawing.Size(70, 13);
            this.labelTemperature.TabIndex = 4;
            this.labelTemperature.Text = "Temperature:";
            // 
            // textCity
            // 
            this.textCity.Location = new System.Drawing.Point(188, 82);
            this.textCity.Name = "textCity";
            this.textCity.Size = new System.Drawing.Size(121, 20);
            this.textCity.TabIndex = 5;
            // 
            // textWeatherCondition
            // 
            this.textWeatherCondition.Location = new System.Drawing.Point(188, 182);
            this.textWeatherCondition.Name = "textWeatherCondition";
            this.textWeatherCondition.Size = new System.Drawing.Size(121, 20);
            this.textWeatherCondition.TabIndex = 6;
            // 
            // textTemperature
            // 
            this.textTemperature.Location = new System.Drawing.Point(188, 215);
            this.textTemperature.Name = "textTemperature";
            this.textTemperature.Size = new System.Drawing.Size(121, 20);
            this.textTemperature.TabIndex = 7;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(335, 265);
            this.Controls.Add(this.textTemperature);
            this.Controls.Add(this.textWeatherCondition);
            this.Controls.Add(this.textCity);
            this.Controls.Add(this.labelTemperature);
            this.Controls.Add(this.labelWeatherCondition);
            this.Controls.Add(this.labelCity);
            this.Controls.Add(this.buttonGetWeather);
            this.Controls.Add(this.groupBox1);
            this.Name = "Form1";
            this.Text = "Weather Client";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton radioButtonFahrenheit;
        private System.Windows.Forms.RadioButton radioButtonCelsius;
        private System.Windows.Forms.Button buttonGetWeather;
        private System.Windows.Forms.Label labelCity;
        private System.Windows.Forms.Label labelWeatherCondition;
        private System.Windows.Forms.Label labelTemperature;
        private System.Windows.Forms.TextBox textCity;
        private System.Windows.Forms.TextBox textWeatherCondition;
        private System.Windows.Forms.TextBox textTemperature;
    }
}

