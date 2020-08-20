function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.var["rtDW"] = {file: "F:\\railway_stpa\\train_model_ert_rtw\\train_model.c",
	size: 58};
	 this.metricsArray.var["rtM_"] = {file: "F:\\railway_stpa\\train_model_ert_rtw\\train_model.c",
	size: 8};
	 this.metricsArray.var["rtU"] = {file: "F:\\railway_stpa\\train_model_ert_rtw\\train_model.c",
	size: 2};
	 this.metricsArray.var["rtY"] = {file: "F:\\railway_stpa\\train_model_ert_rtw\\train_model.c",
	size: 41};
	 this.metricsArray.fcn["train_model_initialize"] = {file: "F:\\railway_stpa\\train_model_ert_rtw\\train_model.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["train_model_step"] = {file: "F:\\railway_stpa\\train_model_ert_rtw\\train_model.c",
	stack: 41,
	stackTotal: 41};
	 this.getMetrics = function(token) { 
		 var data;
		 data = this.metricsArray.var[token];
		 if (!data) {
			 data = this.metricsArray.fcn[token];
			 if (data) data.type = "fcn";
		 } else { 
			 data.type = "var";
		 }
	 return data; }; 
	 this.codeMetricsSummary = '<a href="train_model_metrics.html">Global Memory: 109(bytes) Maximum Stack: 41(bytes)</a>';
	}
CodeMetrics.instance = new CodeMetrics();
