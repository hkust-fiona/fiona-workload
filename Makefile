XLEN ?= 64

default: all

src_dir = ./
target_dir = ./build

#--------------------------------------------------------------------
# Sources
#--------------------------------------------------------------------

applications = \
	hello_fiona		\
	math_palu		\
	math_ealu		\
	math_nlu		\
	math_misc		\
	nn_linear		\
	nn_conv			\
	nn_pad			\
	nn_pool			\
	mlp_iris

#--------------------------------------------------------------------
# Build rules
#--------------------------------------------------------------------

incs  += -I$(src_dir)/lib $(addprefix -I$(src_dir)/app/, $(applications))
objs  :=

RISCV_PREFIX ?= riscv$(XLEN)-unknown-elf-
RISCV_GXX ?= $(RISCV_PREFIX)g++
RISCV_GXX_OPTS ?= -static -std=gnu++11 -O2 -ffast-math -fno-tree-loop-distribute-patterns 
RISCV_LINK ?= $(RISCV_GXX) $(incs)
RISCV_LINK_OPTS ?= -static -lm -lstdc++
RISCV_OBJDUMP ?= $(RISCV_PREFIX)objdump --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.text.init --section=.data
RISCV_OBJCOPY ?= $(RISCV_PREFIX)objcopy -S --set-section-flags .bss=alloc,contents -O binary 
RISCV_SIM ?= spike pk --isa=rv$(XLEN)gc --extension=fiona


define compile_template
$(target_dir)/$(1).elf: $(wildcard $(src_dir)/app/$(1)/*)
	mkdir -p $(target_dir)
	$$(RISCV_GXX) $$(incs) $$(RISCV_GXX_OPTS) -o $$@ \
		$(wildcard $(src_dir)/app/$(1)/*.c) \
		$(wildcard $(src_dir)/app/$(1)/*.cc) \
		$(wildcard $(src_dir)/app/$(1)/*.S) \
		$(wildcard $(src_dir)/lib/math/*.c) \
		$(wildcard $(src_dir)/lib/math/*.cc) \
		$(wildcard $(src_dir)/lib/math/*.S) \
		$(wildcard $(src_dir)/lib/nn/*.c) \
		$(wildcard $(src_dir)/lib/nn/*.cc) \
		$(wildcard $(src_dir)/lib/nn/*.S) \
		$(wildcard $(src_dir)/lib/utils/*.c) \
		$(wildcard $(src_dir)/lib/utils/*.cc) \
		$(wildcard $(src_dir)/lib/utils/*.S) \
		$$(RISCV_LINK_OPTS)
	$$(RISCV_OBJDUMP) $$@ > $$(target_dir)/$(1).S
	$$(RISCV_OBJCOPY) $$@   $$(target_dir)/$(1).bin
endef

$(foreach app,$(applications),$(eval $(call compile_template,$(app))))

#------------------------------------------------------------
# Build and run benchmarks on riscv simulator


apps_bin  = $(addprefix $(target_dir)/, $(addsuffix .elf,  $(applications)))


apps: $(apps_bin)

artifacts += $(apps_bin)

#------------------------------------------------------------
# Default

all: apps


clean:
	rm -rf $(target_dir)
