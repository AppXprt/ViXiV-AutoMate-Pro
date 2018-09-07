.PHONY: clean All

All:
	@echo "----------Building project:[ Automate - Debug ]----------"
	@"$(MAKE)" -f  "Automate.mk"
clean:
	@echo "----------Cleaning project:[ Automate - Debug ]----------"
	@"$(MAKE)" -f  "Automate.mk" clean
